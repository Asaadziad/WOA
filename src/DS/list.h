#ifndef LIST_H
#define LIST_H

typedef void* Element;

typedef void (*elemDestroy)(Element);
typedef void (*elemPrint)(Element);

typedef struct node_t* Node;
typedef struct list_t* List;

typedef enum { LIST_SUCCESS, LIST_NULL_ARG, LIST_FAILED, LIST_ALLOCATION_FAIL, } ListResult;

List listCreate(elemDestroy destroy_function,elemPrint print_function);

ListResult listInsert(List list, Element element);
void listDestroy(List list);
void listEmpty(List list);
void listPrint(List list);

size_t getListSize(List list);
Node getHead(List list);
Element getNodeData(Node node);
Node getNextNode(Node node);


#endif