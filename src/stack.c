#include "stack.h"
#include "stdlib.h"
#include "memory.h"

#define STACK_START 10

STACK initStack(elemDestroy destroyFunction){
    STACK s = (STACK)malloc(sizeof(*s));
    if(!s) return NULL;
    s->current = 0;
    s->top = 0;
    s->elements = NULL;
    s->destroyFunction = destroyFunction;
    return s;
}

void destroyStack(STACK s){
    int i = s->current;
    while(i > 0){
        pop(s);
        i--;
    }
}

void push(STACK s, StackElement element){

}
void pop(STACK s){
   s->destroyFunction(s->elements[s->current]);
   s->current--;
}
