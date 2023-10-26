#ifndef LIST_H
#define LIST_H

typedef void* Element;

typedef void (*elemDestroy)(Element);

typedef struct node_t* Node;
typedef struct list_t* List;

List listCreate(elemDestroy destroy_function);

void listInsert(List list, Element element);
void listDestroy(List list);

#endif