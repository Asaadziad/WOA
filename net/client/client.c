#include "stdio.h"
#include "../object.h"
#include "arpa/inet.h"
#include "../utils/util.h"
#include "stdlib.h"

int main(int argc, char** argv) {
    char* ip = "127.0.0.1";
    int port = 8080; 

    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0){
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);


    printf("[STARTING STREAM SERVER]\n");
    OBJECT obj = malloc(sizeof(*obj));
    obj->x = 69;
    obj->y = 420;
    Byte* buffer = serialize(obj);  
    sendto(sockfd, buffer, sizeof(buffer),0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("[DATA SENT]\n");

    Byte* msg = malloc(1024);  
    socklen_t len = sizeof(server_addr);
    recvfrom(sockfd, msg, 1024,0, (struct sockaddr*)&server_addr, &len); 
    printf("[Message] %s\n", msg);
}
