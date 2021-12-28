#include "server.h"

void conn();

void server(){
    int server_fd, new_socket;
    char buffer[1024] = "";  
    int i = 0;  
    int socklist[MAXCLIENTS];

    int opt = 1;
    int read_size;
    
    char *hello = "Hello from server";
    struct sockaddr_in server;
    int addrlen = sizeof(server);

    pid_t client_id;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))==0){
        ERROR("\nSocket creation error\n");
    }

    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        ERROR("\nsetsockopt failed\n");
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server, sizeof(server))<0){
            ERROR("\nBind failed\n");
    }

    if(listen(server_fd, MAXCLIENTS*2)<0){
        ERROR("\nListen error\n");        
    }
    while(new_socket = accept(server_fd, (struct sockaddr*)&server, (socklen_t*)&addrlen)){
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