#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "task.h"
#include "stdint.h"
#include "object.h"
#include "player.h"

typedef struct tmanager_t* TaskManager;

TaskManager taskManagerInit();

void addTask(TaskManager manager,uint32_t id,TaskType type);
void handleTasks(TaskManager manager,Player p);


#endif