#include "stdlib.h"
#include "stdio.h"
#include "assert.h"

#include "../DS/list.h"

static void printInt(Element x){
    int* test = x;
    printf("%d - ",*test);
}

void list_create(){
    List l = listCreate(NULL,printInt);
    int* loser = (int*)malloc(sizeof(int));
    *loser = 9;
    int* winner = (int*)malloc(sizeof(int));
    *winner = 10;
    assert(listInsert(l,loser) == LIST_SUCCESS);
    assert(listInsert(l,winner) == LIST_SUCCESS);
    listDestroy(l);
}

void list_print(){
    List l = listCreate(NULL,printInt);
    int* loser = (int*)malloc(sizeof(int));
    *loser = 9;
    int* winner = (int*)malloc(sizeof(int));
    *winner = 10;
    assert(listInsert(l,loser) == LIST_SUCCESS);
    assert(listInsert(l,winner) == LIST_SUCCESS);
    listPrint(l);
    listDestroy(l);
}
