#include "unistd.h"
#include "arpa/inet.h"
#include "stdlib.h"
#include "stdio.h"
#include "../utils/util.h"

int main() {
    char* ip = "127.0.0.1";
    int port = 8080; 

    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[8];
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0){
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    int e;
    e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(e < 0){
        exit(1);
    }
    int n;
    socklen_t len;
    
    len = sizeof(client_addr);
    n = recvfrom(sockfd, &buffer, 8,0, (struct sockaddr*)&client_addr, &len);
         
    OBJECT o = malloc(sizeof(*o));
    o->x = readInteger(buffer, 0);
    o->y = readInteger(buffer, 4);
    char* msg = malloc(41);
    sprintf(msg, "[SERVER RECIEVED] Object{x : %d, y : %d}", o->x, o->y);
    sendto(sockfd, msg, 41, 0, (struct sockaddr*)&client_addr, sizeof(client_addr)); 
}