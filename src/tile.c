#include "tile.h"
#include "stdlib.h"


Tile createTile(int x, int y,TileType type){
    Tile t = (Tile)malloc(sizeof(*t));
    if(!t) return NULL;
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.h = 50;
    dst.w = 50;
    t->tile_box = dst;
    t->type = type;
    
    return t;
}

void destroyTile(Tile t){
    if(!t) return;
    free(t);
}

