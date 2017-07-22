#ifndef ANDYSERVER_H
#define ANDYSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>

int getPort();
void checkSocket();
void printUsageError();
void setupShutdown();
void serverClose();
void setupCHLDaction();
void decChildCount();

#endif
