#include "stdlib.h"

#include "DS/queue.h"

#include "taskManager.h"
#include "task.h"
#include "stdint.h"
#include "logger.h"
#include "stdio.h"
#include "Player/playerWalk.h"
#include "player.h"
#include "Player/playerFishing.h"

struct tmanager_t
{
    QUEUE tasks;    
};

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


/*
*   Tasks are saved in a queue (FIFO) and handeled accordingly.
*/
void handleTasks(TaskManager manager,Player p){
    QUEUE q = manager->tasks;
    if(!q) return;
    TASK t = (TASK)getFirstElement(q);
    if(!t) {return;}
    switch (getTaskType(t)){
        case PLAYER_WALK_2OBJECT_TASK:
        //playerWalkToObject(t,p,p->target_object);
        break;
        case PLAYER_WALK_TASK:
        //playerWalkTo(t,p,p->target_position.x,p->target_position.y);
        break;
        case FISHING_SKILL_TASK:
            startFishing(t,p);
        break;
        default:break;
    }
    if(isTaskFinished(t)){
        queuePop(q);
    }
}

