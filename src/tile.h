#ifndef TILE_H
#define TILE_H

#include "SDL2/SDL.h"
#include "vector.h"

#define TILE_WIDTH 25
#define TILE_HEIGHT 25

typedef enum {
    WATER_TILE,
    GRASS_TILE,
    BLOCK_TILE,
} TileType;

typedef struct {
    SDL_Rect tile_box;
    TileType type;
} *Tile;

Tile createTile(int x, int y,TileType type);
void renderTile(Tile tile);
void destroyTile(Tile t);

#endif