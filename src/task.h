#ifndef TASK_H
#define TASK_H

#include "stdint.h"

typedef enum {
    PLAYER_WALK_TASK,
    SKILL_TASK,
} TaskType;

typedef struct task_t* TASK;

TASK createTask(uint32_t id,TaskType type);
void destroyTask(TASK task);

uint32_t getTaskId(TASK task);
uint8_t isTaskFinished(TASK task);
void markTaskFinished(TASK task);

#endif