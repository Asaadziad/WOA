#ifndef UTIL_H
#define UTIL_H

#include "../object.h"

typedef unsigned char Byte;

void printBits(Byte* stream,int byte_count);
void readBytes(Byte* stream, int byte_count);
void serializeInt(Byte* int_stream, int offset, int i);
void serializeString(Byte* str_stream, int offset, char* string);
Byte* serialize(OBJECT obj);

int readInteger(Byte* stream, int offset);

#endif