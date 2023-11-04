#include "stdlib.h"

#include "DS/queue.h"

#include "taskManager.h"
#include "task.h"
#include "stdint.h"

struct tmanager_t
{
    QUEUE tasks;    
};
void handleTasks(TaskManager manager);
static void destroyTaskPtr(void* t){
    destroyTask((TASK)t);
}


TaskManager taskManagerInit(){
    TaskManager t = (TaskManager)malloc(sizeof(*t));
    if(!t) return NULL;
    t->tasks = createQueue(destroyTaskPtr,NULL);
    return t;
}

void addTask(TaskManager manager,uint32_t id,TaskType type){
    TASK new_t = createTask(id,type);
    if(!new_t) return;
    queuePush(manager->tasks,new_t);
}

void handleTasks(TaskManager manager){
    QUEUE q = manager->tasks;
    if(!q) return;
    TASK t = (TASK)getFirstElement(q);
    if(!t) return;
    while(isTaskFinished(t)){
        //CODE to do the task

        //when finished mark it
        markTaskFinished(t);
        queuePop(q);
        //get the next task
        t = (TASK)getFirstElement(q);
    }
}
