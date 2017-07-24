#include "http.h"

void fulfillRequest(int clientsocket) {
   char * request = parseRequest(clientsocket);
   send(clientsocket, request, sizeof(request), 0);
}

char * parseRequest(int clientsocket) {
   char * request = (char *) calloc(8192, 1);
   recv(clientsocket, request, sizeof(request), MSG_WAITALL);
   return request;
}
