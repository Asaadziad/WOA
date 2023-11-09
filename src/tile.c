#include "tile.h"
#include "stdlib.h"


Tile createTile(int x, int y,int height, int width,TileType type){
    Tile t = (Tile)malloc(sizeof(*t));
    if(!t) return NULL;
    SDL_Rect src;
    src.x = x;
    src.y = y;
    src.h = height;
    src.w = width;
    t->tile_box = src;
    t->type = type;
    return t;
}

void destroyTile(Tile t){
    if(!t) return;
    free(t);
}

