#include "list.h"
#include "stddef.h"
#include "stdlib.h"

struct node_t
{
    Element data;
    Node next;
};

struct list_t {
    Node head;
    size_t size;
    elemDestroy destroy_function;
};

/*
* Creates an empty list
*/
List listCreate(elemDestroy destroy_function){
    List list = (List)malloc(sizeof(*list));
    if(!list) return NULL;
    list->head = NULL;
    list->size = 0;
    list->destroy_function = destroy_function;
    return list;
}

static Node nodeCreate(Element element){
    Node e = (Node)malloc(sizeof(*e));
    if(!e) return NULL;
    e->data = element;
    e->next = NULL;
    return e;
}


/*
* Inserts at the end of the list
*/
void listInsert(List list, Element element){
    if(!list || !element) return;
    Node current = list->head;
    if(!current) return;
    while (current->next)
    {
        current = current->next;
    }
    Node next = nodeCreate(element);
    if(!next) return;
    current->next = next;  
}

void listDestroy(List list){
    if(!list) return;
    Node current = list->head;
    while(current != NULL){
        Node tmp = current->next;
        list->destroy_function(current->data);
        current->next = NULL;
        free(current);
        current = tmp;
    }
}
