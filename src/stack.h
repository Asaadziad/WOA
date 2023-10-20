/*
* Implementing generic stack in case i needed it more often
*/
#ifndef STACK_H
#define STACK_H

#include "stddef.h"

#define PUSH(stack,element,type) \
    push(stack,(type)element)

typedef void* StackElement;

typedef void (*elemDestroy)(StackElement); 

typedef struct {
    StackElement* elements;
    size_t current;
    size_t top;
    elemDestroy destroyFunction;
} *STACK;

STACK initStack(elemDestroy destroyFunction);
void destroyStack(STACK s);

void push(STACK s, StackElement element);
void pop(STACK s);

#endif