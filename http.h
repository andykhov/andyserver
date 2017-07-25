#ifndef HTTP_H
#define HTTP_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <math.h>

void fulfillRequest();
char * getRequest();
void sendHeader();
void sendOKHeader();
void sendBadRequestHeader();
void sendNotFoundHeader();
void sendDeniedHeader();

#endif
