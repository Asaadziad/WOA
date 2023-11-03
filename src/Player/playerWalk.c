#include "playerWalk.h"
#include "../logger.h"

void playerWalkTo(Game game, Player p, int x, int y){
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
}

void playerWalkToObject(Game game,Player p, OBJECT obj){
    SDL_Rect src = objectGetRect(obj);
    playerWalkTo(game,p,src.x,src.y);
}