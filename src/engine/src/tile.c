#include "stdlib.h"

#include "headers/tile.h"


Tile createTile(int x, int y,TileType type){
    Tile t = (Tile)malloc(sizeof(*t));
    if(!t) return NULL;
    t->type = type;
    t->worldX = x;
    t->worldY = y;
    return t;
}

TileType getTileType(Tile tile){
    if(!tile) return EARTH_TILE;
    return tile->type;
}
int getTileWorldX(Tile tile){
    if(!tile) return 0;
    return tile->worldX;
}
int getTileWorldY(Tile tile){
    if(!tile) return 0;
    return tile->worldY;
}

void destroyTile(Tile t){
    if(!t) return;
    free(t);
}

