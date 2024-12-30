#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"

#include "headers/list.h"

struct node_t
{
    Element data;
    Node next;
    Node prev;
};

struct list_t {
    Node head;
    Node tail;
    size_t size;
    elemDestroy destroy_function;
    elemFind compare_function;
    elemPrint print_function;
};

/*
* Creates an empty list
*/
List listCreate(elemDestroy destroy_function,elemFind compare_function,elemPrint print_function){
    List list = (List)malloc(sizeof(*list));
    if(!list) return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->destroy_function = destroy_function;
    list->compare_function = compare_function;
    list->print_function = print_function;
    return list;
}

static Node nodeCreate(Element element){
    Node e = (Node)malloc(sizeof(*e));
    if(!e) return NULL;
    e->data = element;
    e->next = NULL;
    e->prev = NULL;
    return e;
}

static void nodeDestroy(Node node,elemDestroy destroy){
    if(!node) return;
    if(destroy == NULL){
        free(node->data);
    } else { 
        destroy(node->data); 
    }
    
   if(node){
    node->next = NULL;
    node->prev = NULL;
    free(node);
   }

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
        list->tail = new;
        list->size++;
        return LIST_SUCCESS;
    }
    list->tail->next = new;
    list->tail = new;
    list->size++;
    return LIST_SUCCESS;
}

ListResult listInsertTail(List list,Element element){
    if(!list || !element) return LIST_NULL_ARG;
    Node new = nodeCreate(element);
    if(!new) return LIST_ALLOCATION_FAIL;
    if(!list->tail && !list->head){
        list->head = new;
        list->tail = new;
        list->size++;
        return LIST_SUCCESS;
    }
    if(list->tail){
        Node current_tail = list->tail;
        new->prev = current_tail;
        current_tail->next = new;
        list->tail = new;
    }
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
    list->tail = NULL;
    list->size = 0;
}


void listDestroy(List list){
    if(!list) return;
    listEmpty(list);
    free(list);
}

void listPrint(List list){
    if(!list) return;
    loopAndMap(list,list->print_function);
    printf("\n");
}

Element listFind(List list, Element element){
    if(!list) return NULL;
    Node current = list->head;
    while(current != NULL){
        Node tmp = current->next;
        if(list->compare_function(current->data,element)){
            return current->data;
        }
        current = tmp;
    }
    return NULL;
}

size_t getListSize(List list){
  if(!list) return 0;
  return list->size;
}

Node getHead(List list){
  if(!list) return NULL;
  return list->head;
}

ListResult removeHead(List list){
    if(!list) return LIST_NULL_ARG;
    Node tmp = list->head->next;
    if(!tmp){
        listEmpty(list);
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
        return LIST_SUCCESS;
    }
    if(list->head == list->tail){
        listEmpty(list);
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
        return LIST_SUCCESS;
    }
    Node current_head = list->head;
    current_head->next = NULL;
    tmp->prev = NULL;
    list->head = tmp;
    nodeDestroy(current_head,list->destroy_function);
    list->size--;
    return LIST_SUCCESS;
}
ListResult setHead(List list,Node node){
    if(!node || !list) return LIST_NULL_ARG;
    node->prev = NULL;
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
    return LIST_SUCCESS;
}


Element getNodeData(Node node){
  if(!node) return NULL;
  return node->data;
}

Node getNextNode(Node node){
  if(!node) return NULL;
  return node->next;
}
