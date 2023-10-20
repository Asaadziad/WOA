#include "tile.h"
#include "stdlib.h"

Tile createTile(){
    Tile t = (Tile)malloc(sizeof(*t));
    if(!t) return NULL;
    Vector2f pos = {0,0};
    Vector2f vel = {10,10};
    t->texture = NULL;
    t->velocity = vel;
    t->current_position = pos;
    return t;
}

void destroyTile(Tile t){
    SDL_DestroyTexture(t->texture);
    free(t);
}