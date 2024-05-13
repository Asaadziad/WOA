#include "util.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

void printBits(Byte* stream, int byte_count) {
    printf("Bytes[");
    for(int i = 0; i < byte_count;i++){
        if (i > 0){
            printf(", ");
        }
        printf("%d", stream[i]);
    }
    printf("]\n");

}

void readBytes(Byte* stream, int byte_count){
    if(!stream) {
        printf("Error: bytes stream is null");
        return;
    }
   for(int i = 0;i<byte_count;i++){
    printf("byte %d - ",i);
    printf("%d\n", stream[i]);
   }    
}

void serializeInt(Byte* int_stream, int offset, int i) {
    int_stream[offset] = i & 0xff;
    int_stream[offset+1] = i >> 8 & 0xff;
    int_stream[offset+2] = i >> 16 & 0xff;
    int_stream[offset+3] = i >> 24 & 0xff;    
}

void serializeString(Byte* str_stream, int offset, char* string) {
    int len = strlen(string);
    for(int i = 0 ; i < len;i++) {
        if(i > 1023) return;
        str_stream[offset + i] = string[i];
    }
}

Byte* serialize(OBJECT obj) {
    int byte_count = sizeof(*obj);
    Byte* bytes = malloc(byte_count); 
    serializeInt(bytes, 0, obj->x);
    serializeInt(bytes,4, obj->y);      
    return bytes;
}

int readInteger(Byte* stream, int offset){
    int byte1 = stream[offset];
    int byte2 = stream[offset + 1] << 8;
    int byte3 = stream[offset + 2] << 16;
    int byte4 = stream[offset + 3] << 24;
    
    return byte1 + byte2 + byte3 + byte4;
}
