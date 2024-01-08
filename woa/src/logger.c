#include "../headers/logger.h"
#include "stdio.h"

void LOG(const char* message){
    fprintf(stderr,"[LOG] : %s\n",message);    
}
void ERR(const char* message){
    fprintf(stderr,"[ERROR] : %s\n",message);
}