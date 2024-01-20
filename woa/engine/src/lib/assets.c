#include "stdlib.h"

#include "../../../headers/assets.h"
#include "stdio.h"
#include "string.h"

char* int2string(int x) {
    int tmp = x;
    int len = 0;
    while(tmp > 0){
        len++;
        tmp = tmp/10;    
    }
    char* result = (char*)malloc(sizeof(*result)*(len+1));
    tmp = x;
    int i = len;
    result[i] = '\0';
    i--;
    while(tmp > 0){
        result[i] = tmp%10 + '0';
        tmp = tmp / 10;
        i--;
    }
    return result;
}

