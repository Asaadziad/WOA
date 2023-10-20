#include "player.h"
#include "stdlib.h"
#include "memory.h"

#define TILE_STARTER 10

Player initPlayer(int x,int y,int width,int height){
    Player new_p = (Player)malloc(sizeof(*new_p));
    if(!new_p) return NULL;
    new_p->position.x = x;
    new_p->position.y = y;
    new_p->width = width;
    new_p->height = height;
    // Player created in standing position therefore it doesnt move.
    new_p->isMoving = false;
    Vector2f vel = {10,10};
    new_p->vel = vel;
    new_p->tiles = initStack(destroyTile);
    return new_p;
}

void pushTile(Player p,Tile tile){
    push(p->tiles,tile);
}
void popTile(Player p){
    pop(p->tiles);
}
