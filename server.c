#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

#define PORT 22
void *conn(void *args);
char buffer[1024] = "";  
int i = 0;  
int socklist[5];
void server(){

    int server_fd, new_socket;
    int opt = 1;
    int read_size;
    
    char *hello = "Hello from server";
    struct sockaddr_in server;
    int addrlen = sizeof(server);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))==0){
        printf("\nSocket creation error\n");
    }

    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        printf("\nsetsockopt failed\n");
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server, sizeof(server))<0){
            printf("\nBind failed\n");
    }

    if(listen(server_fd, 5)<0){
        printf("\nListen error\n");        
    }
    while(new_socket = accept(server_fd, (struct sockaddr*)&server, (socklen_t*)&addrlen)){
        socklist[i] = new_socket;
        printf("\nConnection accepted\n");
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, conn, &new_socket);
        i++;
       

    }
    

    
    

    

    
    

}         

void *conn(void *args){
    int sock = *((int*)args);
    

        
        while(recv(sock, buffer, 1024, 0)>0){
            printf("%s", buffer);
            for (int q = 0; q <= 5; q++){
                send(socklist[q], buffer, strlen(buffer), 0);
            }
            
            bzero(buffer, 1024);
            
        }
       
    
   
    printf("\nClient disconnected\n");
}