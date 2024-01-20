#include "stdbool.h"
#include "stdint.h"
#include "stdlib.h"

#include "../../headers/task.h"


struct task_t {
    uint32_t task_id;
    bool isFinished;    
    TaskType type;
};

TASK createTask(uint32_t id,TaskType type){
    TASK new_t = (TASK)malloc(sizeof(*new_t));
    if(!new_t) return NULL;
    new_t->task_id = id;
    new_t->isFinished = false;
    new_t->type = type;
    return new_t;    
}

void destroyTask(TASK task){
    free(task);
}


uint32_t getTaskId(TASK task){
    if(!task) return 0;
    return task->task_id;
}

void markTaskFinished(TASK task){
    if(!task) return;
    task->isFinished = true;
}

uint8_t isTaskFinished(TASK task){
    if(!task) return 0;
    return task->isFinished;
}

TaskType getTaskType(TASK task){
    return task->type;
}