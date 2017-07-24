#include "andyserver.h"
#include "connection.h"

#define QUEUESIZE 10
#define ON 1

static int children = 0;
static int localsocket;

int main(int argc, char **argv) {
   int port = getPort(argc, argv);
   localsocket = setupLocalSocket((unsigned short) port, QUEUESIZE);
   checkSocket(localsocket);
   setupShutdown();
   setupCHLDaction();
   enableServer(port);
   return 0;
}

void enableServer(int port) {
   printf("andyserver enabled on port %d...\nlistening for client requests\n", port);

   while (ON) listenForClients();
}

void listenForClients() {
   int clientsocket;
   pid_t childPid;

   clientsocket = connectToClient(localsocket);
   children++;

   if ((childPid = fork()) < 0) {
      children--;
      printf("internal error: fork\n");
   }

   else if (childPid == 0) {
      printf("here\n");
      exit(0); /* serve request */
   }
}

void checkSocket(int socketfd) {
   if (socketfd < 0) {
      printf("socket error, could be port #\n");
      exit(1);
   }
}

/* returns indicated port # from command line args */
int getPort(int argc, char **argv) {
   int port;

   if (argc != 2) exitUsageError();

   port = atoi(argv[1]);

   /* 1-1024 are reserved port #'s
    * 65535 is the max port # in IPv4 */
   if (port <= 1024 || port > 65535) exitUsageError();

   return port;
}

void exitUsageError() {
   printf("Usage: andyserver <port>, 1024 < port < 65535\n");
   exit(1);
}

/* setup shutdown mechanism for server
 * server closes by a SIGINT or a SIGTSTP
 * paired with serverClose() */
void setupShutdown() {
   struct sigaction shutdownAction;
   shutdownAction.sa_handler = serverClose;
   sigemptyset(&(shutdownAction.sa_mask));
   sigaddset(&(shutdownAction.sa_mask), SIGINT);
   sigaddset(&(shutdownAction.sa_mask), SIGTSTP);
   sigaction(SIGINT, &shutdownAction, NULL);
   sigaction(SIGTSTP, &shutdownAction, NULL);
}

/* closes server
 * waits for child processes to close */
void serverClose() {
   while (children);
   shutdown(localsocket, SHUT_RDWR);
   exit(0);
}

/* setup mechanism for when a child process closes
 * paired with decChildCount() */
void setupCHLDaction() {
   struct sigaction chldAction;
   chldAction.sa_handler = decChildCount;
   sigemptyset(&(chldAction.sa_mask));
   sigaddset(&(chldAction.sa_mask), SIGCHLD);
   sigaction(SIGCHLD, &chldAction, NULL);
}

void decChildCount() {
   children--;
}
