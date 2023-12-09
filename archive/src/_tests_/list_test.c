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

void listInsertAtTail(){
    List l = listCreate(NULL,printInt);
    int* loser = (int*)malloc(sizeof(int));
    *loser = 9;
    int* winner = (int*)malloc(sizeof(int));
    *winner = 10;
    int* winner2 = (int*)malloc(sizeof(int));
    *winner2 = 12;
    int* winner3 = (int*)malloc(sizeof(int));
    *winner3 = 13;
    int* winner4 = (int*)malloc(sizeof(int));
    *winner4 = 14;
    int* winner5 = (int*)malloc(sizeof(int));
    *winner5 = 15;
    assert(listInsertTail(l,loser) == LIST_SUCCESS);
    assert(listInsertTail(l,winner) == LIST_SUCCESS);
    assert(listInsertTail(l,winner2) == LIST_SUCCESS);
    assert(listInsertTail(l,winner3) == LIST_SUCCESS);
    assert(listInsertTail(l,winner4) == LIST_SUCCESS);
    assert(listInsertTail(l,winner5) == LIST_SUCCESS);
    listPrint(l);
    listDestroy(l);
}
