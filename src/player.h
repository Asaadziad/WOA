#ifndef PLAYER_H
#define PLAYER_H

#include "stdbool.h"
#include "vector.h"
#include "tile.h"
#include "object.h"

typedef enum {
    NORTH,
    SOUTH,
    WEST,
    EAST,
} PlayerFace;

typedef struct player_t {
    Vector2f position;
    Vector2f vel;
    int height;
    int width;
    bool isMoving;
    PlayerFace face;
    OBJECT target_object;
    Vector2f target_position;
    int level;
    uint32_t current_xp;
} *Player;

Player initPlayer(int x,int y,int width,int height);
void destroyPlayer(Player p);

#endif