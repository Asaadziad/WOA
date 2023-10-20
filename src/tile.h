#ifndef TILE_H
#define TILE_H

#include "SDL2/SDL.h"
#include "vector.h"

typedef struct {
    Vector2f current_position;
    Vector2f velocity;
    SDL_Texture* texture;
} *Tile;

Tile createTile();
void destroyTile(Tile t);

#endif