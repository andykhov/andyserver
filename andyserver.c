#include "andyserver.h"

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
