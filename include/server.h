#ifndef SERVER_H_
    #define SERVER_H_

#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

#include "../include/ErrorDebugMacros.h"

void server();

#define MAXCLIENTS 100
#define PORT 6969

#endif //SERVER_H_