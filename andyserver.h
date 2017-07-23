#ifndef ANDYSERVER_H
#define ANDYSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>

void enableServer();
void listenForClients();
int getPort();
void checkSocket();
void exitUsageError();
void setupShutdown();
void serverClose();
void setupCHLDaction();
void decChildCount();

#endif
