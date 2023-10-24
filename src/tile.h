#ifndef TILE_H
#define TILE_H

#include "SDL2/SDL.h"
#include "vector.h"

#define TILE_WIDTH 25
#define TILE_HEIGHT 25

typedef struct {
    Vector2f current_position;
    Vector2f velocity;
} *Tile;

Tile createTile(int x, int y,int vel_x,int vel_y);
void destroyTile(Tile t);

#endif