#include "andyserver.h"
#include "connection.h"

#define QUEUESIZE 10

static int children = 0;
static int localsocket;

int main(int argc, char **argv) {
   int port = getPort(argc, argv);
   localsocket = setupLocalSocket((unsigned short) port, QUEUESIZE);
   checkSocket(localsocket);
   setupShutdown();
   setupCHLDaction();
   return 0;
}

void checkSocket(int socketfd) {
   if (socket < 0) {
      printf("socket error, could be port #\n");
      exit(1);
   }
}

/* returns indicated port # from command line args */
int getPort(int argc, char **argv) {
   int port;

   if (argc != 2) {
      printUsageError();
      exit(1);
   }

   port = atoi(argv[1]);

   /* 1-1024 are reserved port #'s
    * 65535 is the max port # in IPv4 */
   if (port <= 1024 || port > 65535) {
      printUsageError();
      exit(1);
   }

   return port;
}

void printUsageError() {
   printf("Usage: andyserver <port>, 1024 < port < 65535\n");
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
