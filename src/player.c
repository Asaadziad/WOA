#include "player.h"
#include "stdlib.h"
#include "memory.h"

#define TILE_STARTER 10

Player initPlayer(int x,int y,int width,int height){
    Player new_p = (Player)malloc(sizeof(*new_p));
    if(!new_p) return NULL;
    Vector2f pos = {x,y};
    new_p->position = pos;
    new_p->width = width;
    new_p->height = height;
    new_p->isMoving = false;
    Vector2f vel = {10,10};
    new_p->vel = vel;
    new_p->face = NORTH;
    new_p->level = 0;
    new_p->current_xp = 0;
    new_p->target_object = NULL;
    return new_p;
}

void destroyPlayer(Player p){
    free(p);
}

