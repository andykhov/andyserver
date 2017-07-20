#ifndef CONNECTION_H
#define CONNECTION_H

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define ERROR -1

int setupLocalSocket(unsigned short port, int queueSize);
int connectToClient(int localsocket);

#endif
