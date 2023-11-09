#ifndef TILE_H
#define TILE_H

#include "SDL2/SDL.h"
#include "vector.h"

#define TILE_WIDTH 20
#define TILE_HEIGHT 20
#define TOTAL_TILES 12
#define TOTAL_TILE_SPRITES 12

//The different tile sprites
#define TILE_RED 0
#define TILE_GREEN 1
#define TILE_BLUE 2
#define TILE_CENTER 3


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