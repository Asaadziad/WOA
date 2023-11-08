#include "player.h"
#include "stdlib.h"
#include "memory.h"

#define TILE_STARTER 10

Player initPlayer(int x,int y,int width,int height){
    Player new_p = (Player)malloc(sizeof(*new_p));
    if(!new_p) return NULL;
    new_p->current_frame = 1;
    Vector2f pos = {x,y};
    new_p->position = pos;
    new_p->width = width;
    new_p->height = height;
    new_p->isMoving = false;
    Vector2f vel = {10,10};
    new_p->vel = vel;
    new_p->face = NORTH;
    new_p->level = 0;
    new_p->current_xp = 0;
    new_p->target_object = NULL;
    new_p->target_position.x = 0;
    new_p->target_position.y = 0;
    return new_p;
}

void playerDraw(TextureManager manager,Player p,SDL_Renderer* renderer){

    if(p->face == EAST){
    drawFrame(manager,PLAYER_TEXTURE,p->position.x,p->position.y,p->width,p->height,1,p->current_frame,renderer,SDL_FLIP_HORIZONTAL);

    } else {
    drawFrame(manager,PLAYER_TEXTURE,p->position.x,p->position.y,p->width,p->height,1,p->current_frame,renderer,SDL_FLIP_NONE);

    }
}

void playerUpdate(Player p){
    p->current_frame = (int)(SDL_GetTicks()/100) % 12;
}


void destroyPlayer(Player p){
    free(p);
}

