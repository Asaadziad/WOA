#include "tile.h"
#include "stdlib.h"

Tile createTile(int x, int y,int vel_x,int vel_y){
    Tile t = (Tile)malloc(sizeof(*t));
    if(!t) return NULL;
    Vector2f pos = {x,y};
    Vector2f vel = {vel_x,vel_y};
    t->velocity = vel;
    t->current_position = pos;
    return t;
}

void destroyTile(Tile t){
    if(!t) return;
    free(t);
}

