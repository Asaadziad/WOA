#ifndef PLAYER_H
#define PLAYER_H

#include "stdbool.h"
#include "vector.h"
#include "tile.h"
#include "stack.h"


typedef struct player_t{
    Vector2f position;
    Vector2f vel;
    int height;
    int width;
    bool isMoving;
    STACK tiles;        
} *Player;

Player initPlayer(int x,int y,int width,int height);
void pushTile(Player p ,Tile tile);
void popTile();

#endif