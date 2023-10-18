#ifndef PLAYER_H
#define PLAYER_H

#include "stdbool.h"

typedef struct player_t{
    int x;
    int y;
    int height;
    int width;
    int vel;
    bool isMoving;
} *Player;

Player initPlayer(int x,int y,int width,int height);

#endif