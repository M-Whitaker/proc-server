// Client side C++ program to demonstrate Socket programming 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>

#include <iostream>

#define PORT 9909
   
int main(int argc, char const *argv[]) 
{ 
    if( argc == 2 ) {
       printf("Connecting to socket at  %s:%d\n", argv[1], PORT);
    }
    else if( argc > 2 ) {
       printf("Too many arguments supplied.\n");
       return 1;
    }
    else {
       printf("One argument expected.\n");
       return 1;
    }
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    const char *hello = "This is a message from the client!"; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    send(sock , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer ); 
    return 0; 
} 
