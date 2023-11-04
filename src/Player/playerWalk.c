#include "playerWalk.h"
#include "../logger.h"

void playerWalkTo(TASK task,Player p, int x, int y){
        if(p->position.x < x){
            p->position.x++;
        } else if(p->position.x > x){
            p->position.x--;
        }

        if(p->position.y < y){
            p->position.y++;
        } else if(p->position.y > y){
            p->position.y--;
        }

    if(p->position.x == x && p->position.y == y){
        markTaskFinished(task);
    }
}



void playerWalkToObject(TASK task,Player p, OBJECT obj){
    SDL_Rect src = objectGetRect(obj);
    playerWalkTo(task,p,src.x + src.w/2,src.y + src.h);
}