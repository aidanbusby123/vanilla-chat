/*    
    This file serves as the server program for vanilla chat
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

#include "../include/server.h"

void conn();

void server(){
    int server_fd, new_socket;
    char buffer[1024] = "";  
    int i = 0;  
    int socklist[MAXCLIENTS];

    int opt = 1;
    
    struct sockaddr_in server;
    int addrlen = sizeof(server);

    pid_t client_id = 0;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))==0){
        ERROR("\nSocket creation error\n");
    }

    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        ERROR("\nsetsockopt failed\n");
    }
    server.sin_family = AF_INET;
    //DEBUG("AF_INET = %d\n", AF_INET); add debug statments later     
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server, sizeof(server))<0){
            ERROR("\nBind failed\n");
    }

    if(listen(server_fd, MAXCLIENTS*2)<0){
        ERROR("\nListen error\n");        
    }
    while((new_socket = accept(server_fd, (struct sockaddr*)&server, (socklen_t*)&addrlen))){
        socklist[i] = new_socket;
        if ((client_id = fork()) == 0){
            while(recv(socklist[i], buffer, 1024, 0)>0){
                printf("%s", buffer);
                for (int q = 0; q < MAXCLIENTS; q++){
                    send(socklist[q], buffer, strlen(buffer), 0);
                }
            
            bzero(buffer, 1024);
            
            }
        }
        printf("\nConnection accepted\n");
        
        i++;
    }
}         