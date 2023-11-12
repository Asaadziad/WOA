#ifndef TILE_H
#define TILE_H

#include "SDL2/SDL.h"
#include "vector.h"

#define TILE_WIDTH 32
#define TILE_HEIGHT 32


typedef enum {
    WATER_TILE,
    GRASS_TILE,
    EARTH_TILE,
} TileType;

typedef struct {
    SDL_Rect tile_box;
    TileType type;
} *Tile;

Tile createTile(int x, int y,int height, int width,TileType type);
void destroyTile(Tile t);

#endif