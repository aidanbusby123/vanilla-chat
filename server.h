#ifndef server
#define server

#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/time.h>
#include<sys/ioctl.h>
#include<math.h>

#define MAXCLIENTS 100
#define MAXLEN 1024
#define PORT 6969

void serverMain();

#endif

