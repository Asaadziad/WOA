#include "player.h"
#include "stdlib.h"


Player initPlayer(int x,int y,int width,int height){
    Player new_p = (Player)malloc(sizeof(*new_p));
    if(!new_p) return NULL;
    new_p->x = x;
    new_p->y = y;
    new_p->width = width;
    new_p->height = height;
    // Player created in standing position therefore it doesnt move.
    new_p->isMoving = false;
    new_p->vel.x = 10;
    new_p->vel.y = 10;

    return new_p;
}
