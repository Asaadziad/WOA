#include "queue.h"
#include "list.h"

#include "stdlib.h"

struct queue_t {
    List data;
};

QUEUE createQueue(elemDestroy destroy_function, elemPrint print_function){
    QUEUE q = (QUEUE)malloc(sizeof(*q));
    if(!q) return NULL;
    q->data = listCreate(destroy_function,print_function);
    if(!q->data) return NULL;
    return q;
}
void destroyQueue(QUEUE q){
    listDestroy(q->data);
    free(q);
}

void queuePush(QUEUE q,Element elem){
    listInsertTail(q->data,elem);
}

void queuePop(QUEUE q){
    removeHead(q->data);
}

Q_ELEMENT getFirstElement(QUEUE q){
    Node head = getHead(q->data);
    if(!head) return NULL;
    return getNodeData(head);
}
