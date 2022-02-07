#ifndef client
#define client

#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<math.h>

#define PORT 6969
#define MAXLEN 1024

void clientMain();
void *sendMsg(void *args);

#endif