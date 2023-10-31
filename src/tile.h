#ifndef TILE_H
#define TILE_H

#include "SDL2/SDL.h"
#include "vector.h"

#define TILE_WIDTH 80
#define TILE_HEIGHT 80
#define TOTAL_TILES 192
#define TOTAL_TILE_SPRITES 12

//The different tile sprites
#define TILE_RED 0
#define TILE_GREEN 1
#define TILE_BLUE 2
#define TILE_CENTER 3
#define TILE_TOP 4
#define TILE_TOPRIGHT 5
#define TILE_RIGHT 6
#define TILE_BOTTOMRIGHT 7
#define TILE_BOTTOM 8
#define TILE_BOTTOMLEFT 9
#define TILE_LEFT 10
#define TILE_TOPLEFT 11


typedef enum {
    WATER_TILE,
    GRASS_TILE,
    BLOCK_TILE,
    LAVA_TILE,
} TileType;

typedef struct {
    SDL_Rect tile_box;
    TileType type;
} *Tile;

Tile createTile(int x, int y,TileType type);
void destroyTile(Tile t);

#endif