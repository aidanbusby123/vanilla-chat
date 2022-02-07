#include"client.h"



int sock;

char addr[20];

void *sendMsg(void *args);

void clientMain(){
    char buffer[MAXLEN];
    int read_size;
    struct sockaddr_in serv_addr;
    
    
    char *hello = "Hello from client";

    
    printf("\nEnter server IP: ");
    scanf("%s",&addr);
    if ((sock = socket(AF_INET, SOCK_STREAM, 0))<0){
        printf("\nSocket creation error\n");
        return;
        
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if(inet_pton(AF_INET, addr, &serv_addr.sin_addr)<=0){
        printf("\nInvalid address\n");
        return;
        
    }
    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        printf("\nConnection failed, please try again\n");
        return;
        
    }        
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, sendMsg, &sock);
   
    while(recv(sock, &buffer, 1024, 0)>0){
        printf("%s", buffer);
    }
       
    
  

}
void *sendMsg(void *args){
    int sock = *((int*)args);
    char message[MAXLEN] = "";
    while (1){
        
        fgets(message, 1024, stdin);
        send(sock, message, strlen(message), 0);
        bzero(message, 1024);
        
    }
}