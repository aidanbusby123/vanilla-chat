/*    
    This file serves as the client program for vanilla chat
    Copyright (C) 2021  Aidan Busby

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, Ma 02110-1301 USA.
*/

#include "../include/client.h"

void *sendMsg(void *args);

void client(){
    int sock = 0;
    
    int read_size;
    struct sockaddr_in serv_addr;
    char buffer[1024] = "";

    size_t buffsize = 20;
    char *addr = NULL;
    
    char *hello = "Hello from client";
    (PORT);
    
    printf("\nEnter server IP: ");

    if(!(addr = (char*)malloc(buffsize * sizeof(char)))){
        ERROR("Error in allocating memory for the addr buffer!");
        exit(EXIT_FAILURE);
    }

    getline(&addr, &buffsize, stdin);
    addr[strcspn(addr, "\n")] = '\0';       //removes any newlines from buffer

    if ((sock = socket(AF_INET, SOCK_STREAM, 0))<0){
        ERROR("Socket creation error!\n");
        return;
        
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if(inet_pton(AF_INET, addr, &serv_addr.sin_addr)<=0){
        ERROR("\nInvalid address\n");
        return;
        
    }

    free(addr);

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        ERROR("\nConnection failed, please try again\n");
        return;
        
    }        
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, sendMsg, &sock);
   
        while(recv(sock, buffer, 1024, 0)>0){
            printf("%s", buffer);
            bzero(buffer, strlen(buffer));
        }
}
void *sendMsg(void *args){
    int sock = *((int*)args);
    char message[1024] = "";
    while (1){
        fgets(message, 1024, stdin);
        send(sock, message, strlen(message), 0);
        bzero(message, 1024);
        
    }
}