#ifndef TILE_H
#define TILE_H

#include "SDL2/SDL.h"

#define TILE_WIDTH 48
#define TILE_HEIGHT 48


typedef enum {
    EARTH_TILE,
    GRASS_TILE,
    WATER_TILE,
} TileType;

typedef struct {
    TileType type;
    int worldX;
    int worldY;
} *Tile;

Tile createTile(int x, int y,TileType type);
void destroyTile(Tile t);

TileType getTileType(Tile tile);
int getTileWorldX(Tile tile);
int getTileWorldY(Tile tile);

#endif