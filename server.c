#include"server.h"

struct sockaddr_in serveraddr;
int server_fd, new_socket;

char buffer[MAXLEN];
int i = 0;
int n = 0;
char c;

int fdsz = 1;
fd_set fd, rfd;



void serverMain(){
    printf("xyz                          \n");
    int opt = 1;    
    int addrlen = sizeof(serveraddr);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))==0){
        printf("\nSocket creation error\n");
    }

    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        printf("\nsetsockopt failed\n");
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&serveraddr, sizeof(serveraddr))<0){
            printf("\nBind failed\n");
    }
    
    if(listen(server_fd, MAXCLIENTS*2)<0){
        printf("\nListen error\n");        
    }
    
    FD_ZERO(&fd);
    FD_SET(server_fd, &fd);
    ioctl(server_fd, FIONBIO);
    while (1){
    
        rfd = fd;
        
        if (select(fdsz+1, &rfd, NULL, NULL, NULL) < 0){
            printf("SELECT ERROR\n");
        }
        
        for (i = 0; i < fdsz+1; i++){
            if (FD_ISSET(i, &rfd)){
                if  (i == server_fd){
                    new_socket = accept(server_fd, (struct sockaddr*)&serveraddr, (socklen_t*)&addrlen);
                    if (new_socket < 0){
                       printf("ERROR: CLIENT NOT ACCEPTED\n");
                    } else {
                        
                        printf("\nNEW CLIENT\n");
                        FD_SET(new_socket, &fd);
                        ioctl(new_socket, FIONBIO);
                        fdsz++;
                        
                    }
                } else {
                    if (recv(i, &buffer, MAXLEN, 0)>0){
                        printf("%s", buffer);
                        printf("\n");
                        for (n = 1; n < fdsz+1; n++){
                            send(n, buffer, strlen(buffer), 0);
                        }
                        bzero(buffer, MAXLEN);
                        printf("recv\n");         
                    }else{
                        printf("recv error\n");
                    }
                }

                    
                    
            }
            
        }
            
    }
        
}
    
