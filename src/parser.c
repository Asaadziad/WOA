#include "parser.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

static void tokenize(int arr[][4],int current_place, char* buffer){
    while(*buffer != ' '){ // Skip name
        buffer++;
    }
    char* current_num = "";
    int i = 0;
    while(*buffer != '\0'){
        if(*buffer == ' ') {
            buffer++;
            continue;
        }
        
        buffer++;
        if(*buffer == ' ') {
            arr[current_place][i] = atoi(current_num);
            fprintf(stderr,"%s",current_num);
            current_num = "";
        }
    }
}

void parse(int arr[][4],int len,const char* file_name){
    FILE* file = fopen(file_name, "r");
    if(!file) {
        fprintf(stderr,"NOT HAPPENING");
        return;}
    char* buffer = NULL;
    size_t line_len = 0;
    int current_place = 0;
    while(getline(&buffer, &line_len, file) != -1){
        tokenize(arr,current_place,buffer);
        fprintf(stderr,"%d",arr[0][0]);
        current_place++;
    }

    fclose(file);
}