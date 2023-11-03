#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

typedef struct task_t* TASK;

TASK createTask();

void destroyTask(TASK task);

#endif