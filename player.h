#ifndef PLAYER_H
#define PLAYER_H

typedef struct player_t{
    int x;
    int y;
} *Player;

Player initPlayer(int x,int y);

#endif