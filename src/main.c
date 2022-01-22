/*    
    This is the main file for vanilla chat, this is where the program starts
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

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<termios.h>
#include<pthread.h>
#include "../include/client.h"
#include "../include/server.h"

char buf[64];
int x = 0;
int y = 0;
char ch;
int opt = 1;
int chng;
struct termios orig_termios;
void disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
void enableRawMode(){
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
  
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
void *readFunc(){
    while(read(STDIN_FILENO, &ch, 1) && ch != '\n'){
            
           
            if (ch == '\033'){
                char seq[3];
                if (read(STDIN_FILENO, &seq[0], 1) != 1) break;
                if (read(STDIN_FILENO, &seq[1], 1) != 1) break;
                
                if (seq[0] == '['){
                    switch (seq[1]){
                        case 'A':
                            if (opt > 1){
                                y--;
                                opt--;
                                chng = 1;
                            }
                            
                            
                            break;
                               
                            
                        case 'B':
                            if (opt < 2){
                                y++;
                                opt++;
                                chng = 1;
                            }
                            
                            break;
                                
                            
                    }
                }
                
            }
        }
        return NULL;
}

int main(){
    printf("This Program Was last Compiled on %s, at %s\n", __DATE__, __TIME__);   
    sleep(2);

    enableRawMode();
    printf("\033[2J");
    printf("\033[H");
    int i = 0;
        printf("\033[30;107mCONNECT TO SERVER\n");
        printf("\033[39;49mSTART SERVER\n");
       
        
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, readFunc, NULL);
        

        while (ch != '\n'){
            snprintf(buf, sizeof(buf), "\033[%d;%dH", y+1 , x+1);
            write(STDIN_FILENO, buf, strlen(buf));
            if(chng == 1){
                if (opt == 1){
                    snprintf(buf, sizeof(buf), "\033[%d;%dH\033[39;49mSTART SERVER", 2, 1);
                    write(STDIN_FILENO, buf, strlen(buf));
                    snprintf(buf, sizeof(buf), "\033[%d;%dH\033[?25l\033[K\033[30;107mCONNECT TO SERVER", y+1, x+1);
                    write(STDIN_FILENO, buf, strlen(buf));
                    
                }
                if (opt == 2){
                    snprintf(buf, sizeof(buf), "\033[%d;%dH\033[39;49mCONNECT TO SERVER", 1, 1);
                    write(STDIN_FILENO, buf, strlen(buf));
                    snprintf(buf, sizeof(buf), "\033[%d;%dH\033[?25l\033[K\033[30;107mSTART SERVER", y+1, x+1);
                    write(STDIN_FILENO, buf, strlen(buf));
                }
                chng = 0;
            } 

            
        }
        disableRawMode();
        printf("\033[2J");
        printf("\033[0;0m");
        if (opt == 1){
            client();
        }
        if (opt == 2){
            server();
        }
        
        return 0;
    }

