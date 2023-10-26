#include "logger.h"
#include "stdio.h"

void Log(const char* message){
    fprintf(stderr,"[LOG] : %s\n",message);    
}
void Err(const char* message){
    fprintf(stderr,"[ERROR] : %s",message);
}