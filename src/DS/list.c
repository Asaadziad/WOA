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
    Node new = nodeCreate(element);
    if(!new) return LIST_ALLOCATION_FAIL;
    Node current = list->head;
    /* IF LIST IS EMPTY */
    if(!current) {
        list->head = new; 
        list->size++;
        return LIST_SUCCESS;
    }
    /* WALK TILL THE END */
    while (current->next)
    {
        current = current->next;
    }
    current->next = new;  
    list->size++;
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

void listEmpty(List list){
    if(!list) return;
    Node current = list->head;
    while(current != NULL){
        Node tmp = current->next;
        nodeDestroy(current,list->destroy_function);
        current = tmp;
    }
    list->head = NULL;
    list->size = 0;
}


void listDestroy(List list){
    listEmpty(list);
    free(list);
}

void listPrint(List list){
    if(!list) return;
    loopAndMap(list,list->print_function);
    printf("\n");
}

size_t getListSize(List list){
    return list->size;
}

Node getHead(List list){
    return list->head;
}

Element getNodeData(Node node){
    return node->data;
}

Node getNextNode(Node node){
    return node->next;
}