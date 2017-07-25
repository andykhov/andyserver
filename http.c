#include "http.h"

/* retrieves request from client and fulfills it */
void fulfillRequest(int clientsocket) {
   char * request = getRequest(clientsocket);
   char * method = strtok(request, " \n\r");
   char * filepath = strtok(NULL, " \n\r");

   if (filepath[0] == '/') filepath++;

   sendHeader(method, filepath, clientsocket);

   /* frees memory allocated to the request */
   free(method);
   /* closes connection to client */
   shutdown(clientsocket, SHUT_RDWR);
}

/* retrieves request, used in fulfillRequest() */
char * getRequest(int clientsocket) {
   char * request = (char *) calloc(8192, 1);
   recv(clientsocket, request, 8192, 0);
   return request;
}

void sendHeader(char * method, char * filepath, int clientsocket) {
   struct stat filestat;
   int statError;

   if (method == NULL || filepath == NULL)
      sendBadRequestHeader(clientsocket);

   else if((statError = stat(filepath, &filestat)) < 0) {
      if (errno == EACCES) sendDeniedHeader(clientsocket);
      else sendNotFoundHeader(clientsocket);
   }

   else sendOKHeader(clientsocket, filestat);
}

void sendOKHeader(int clientsocket, struct stat filestat) {
   char header[] = "HTTP/1.0 200 OK\r\nContent-Length:";
   int filesize = filestat.st_size;
   int stringlength = (ceil(log10(filesize))+1)*sizeof(char);
   char * filelength = (char *) malloc(stringlength);

   snprintf(filelength, stringlength, "%d", filesize);

   send(clientsocket, header, sizeof(header), 0);
   send(clientsocket, filelength, sizeof(filelength), 0);
   send(clientsocket, "\r\n\r\n", 4, 0);
}

void sendBadRequestHeader(int clientsocket) {
   char header[] = "HTTP/1.0 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
   send(clientsocket, header, sizeof(header), 0);
}

void sendNotFoundHeader(int clientsocket) {
   char header[] = "HTTP/1.0 404 Not Found\r\nContent-Length: 0\r\n\r\n";
   send(clientsocket, header, sizeof(header), 0);
}

void sendDeniedHeader(int clientsocket) {
   char header[] = "HTTP/1.0 403 Permission Denied\r\nContent-Length: 0\r\n\r\n";
   send(clientsocket, header, sizeof(header), 0);
}
