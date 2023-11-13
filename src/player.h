#ifndef PLAYER_H
#define PLAYER_H

#include "stdbool.h"
#include "vector.h"
#include "tile.h"
#include "object.h"
#include "TextureManager.h"

typedef enum {
    NORTH,
    SOUTH,
    WEST,
    EAST,
} PlayerFace;

typedef struct player_t {
    int current_frame;
    Vector2f position;
    int screenX;
    int screenY;
    Vector2f vel;
    int height;
    int width;
    int level;
    uint32_t current_xp;
} *Player;

Player initPlayer(int x,int y,int width,int height);
void playerDraw(TextureManager manager,Player p,SDL_Renderer* renderer,SDL_Rect camera);
void playerUpdate(Player p,SDL_Rect camera);
void destroyPlayer(Player p);

#endif