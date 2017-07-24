#ifndef HTTP_H
#define HTTP_H

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

void fulfillRequest();
char * parseRequest();

#endif
