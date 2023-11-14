#ifndef LIST_H
#define LIST_H

#include "stddef.h"
#include "stdbool.h"

typedef void* Element;

typedef void (*elemDestroy)(Element);
typedef bool (*elemFind)(Element,Element);
typedef void (*elemPrint)(Element);

typedef struct node_t* Node;
typedef struct list_t* List;

typedef enum { LIST_SUCCESS, LIST_NULL_ARG, LIST_FAILED, LIST_ALLOCATION_FAIL, } ListResult;

List listCreate(elemDestroy destroy_function,elemFind compare_function,elemPrint print_function);

ListResult listInsert(List list, Element element);
ListResult listInsertTail(List list,Element element);
void listDestroy(List list);
void listEmpty(List list);
Element listFind(List list, Element element);
void listPrint(List list);

size_t getListSize(List list);

Node getHead(List list);
ListResult removeHead(List list);
ListResult setHead(List list,Node node);
Element getNodeData(Node node);
Node getNextNode(Node node);


#endif