#ifndef CLIENT_H_
    #define CLIENT_H_

#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>

#include "ErrorDebugMacros.h"

#define PORT 6969

void *sendMsg(void *args);
void client();

#endif //CLIENT_H_