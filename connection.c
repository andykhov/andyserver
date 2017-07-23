#include "connection.h"

/* returns a new local socket file descriptor */
int setupLocalSocket(unsigned short port, int queueSize) {
   int localsockfd, enable;
   struct sockaddr_in localaddr;
   enable = 1;

   /* creates new socket file descriptor */
   if ((localsockfd = socket(AF_INET, SOCK_STREAM, 0)) == ERROR) return ERROR;

   /*sets socket options for socketfd
    * SOL_SOCKET sets to generic socket option
    * SO_REUSEADDR enabled to restart a TIME_WAIT process on a port/address */
   if (setsockopt(localsockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == ERROR) return ERROR;

   /* setup socket address */
   localaddr.sin_family = AF_INET; /* AF_INET represents IPv4 */
   localaddr.sin_port = htons(port); /* converts host port to network TCP big-endian byte order */
   localaddr.sin_addr.s_addr = INADDR_ANY; /* receive packets from anywhere in system's network interface */
   memset(&(localaddr.sin_zero), 0, 8); /* sets leftover byte to 0 */

   /* associate socket to address */
   if (bind(localsockfd, (struct sockaddr *) &localaddr, sizeof(struct sockaddr)) == ERROR) return ERROR;

   /* begin to accept (or wait for) connection requests */
   if (listen(localsockfd, queueSize) == ERROR) return ERROR;

   return localsockfd;
}

/* returns new socket file descriptor that is connected to client */
int connectToClient(int localsocket) {
   struct sockaddr_in clientaddr;
   socklen_t clientaddrsize = sizeof(clientaddr);
   int clientsocket = -1;

   /* gets 1st pending connection request in queue of localsocket */
   while (clientsocket < 0) {
      clientsocket = accept(localsocket, (struct sockaddr *) &clientaddr, &clientaddrsize);
   }

   return clientsocket;
}
