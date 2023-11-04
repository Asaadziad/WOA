#ifndef QUEUE_H
#define QUEUE_H

// FIFO list based queue
typedef void* Q_ELEMENT;
typedef void (*destroyFunc)(Q_ELEMENT);
typedef void (*printFunc)(Q_ELEMENT);
typedef struct queue_t* QUEUE;

QUEUE createQueue(destroyFunc destroy_function, printFunc print_function);
void destroyQueue(QUEUE q);

void queuePush(QUEUE q,Q_ELEMENT elem);
void queuePop(QUEUE q);

Q_ELEMENT getFirstElement(QUEUE q);

#endif