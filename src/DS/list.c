#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"

#include "list.h"

struct node_t
{
    Element data;
    Node next;
};

struct list_t {
    Node head;
    size_t size;
    elemDestroy destroy_function;
    elemPrint print_function;
};

/*
* Creates an empty list
*/
List listCreate(elemDestroy destroy_function,elemPrint print_function){
    List list = (List)malloc(sizeof(*list));
    if(!list) return NULL;
    list->head = NULL;
    list->size = 0;
    list->destroy_function = destroy_function;
    list->print_function = print_function;
    return list;
}

static Node nodeCreate(Element element){
    Node e = (Node)malloc(sizeof(*e));
    if(!e) return NULL;
    e->data = element;
    e->next = NULL;
    return e;
}

static void nodeDestroy(Node node,elemDestroy destroy){
    if(!node) return;
    if(destroy == NULL){
        
        free(node->data);
    } else { 
        destroy(node->data);
    }
    node->next = NULL;
    free(node);
}


/*
* Inserts at the end of the list
*/
ListResult listInsert(List list, Element element){
    if(!list || !element) return LIST_NULL_ARG;
    Node current = list->head;
    if(!current) {
        Node head = nodeCreate(element);
        if(!head) return LIST_ALLOCATION_FAIL;
        list->head = head; 
        return LIST_SUCCESS;
    }
    while (current->next)
    {
        current = current->next;
    }
    Node next = nodeCreate(element);
    if(!next) return LIST_ALLOCATION_FAIL;
    current->next = next;  
    return LIST_SUCCESS;
}

typedef void (*MAP)(Element);
static void loopAndMap(List list,MAP map){
    if(!list || !map) return;
    Node current = list->head;
    while(current != NULL){
        map(current->data);
        current = current->next;
    }
}

void listDestroy(List list){
    if(!list) return;
    Node current = list->head;
    while(current != NULL){
        Node tmp = current->next;
        nodeDestroy(current,list->destroy_function);
        current = tmp;
    }
    free(list);
}

void listPrint(List list){
    if(!list) return;
    loopAndMap(list,list->print_function);
    printf("\n");
}

