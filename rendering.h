#ifndef RENDERING_H
#define RENDERING_H

#include "SDL2/SDL.h"
#include "game.h"


void render_character(SDL_Renderer* renderer,Game game,int x,int y,int camX,int camY);
void render_fence(Game game,SDL_Rect* src,int i);
void render_monster(Game game,int i);
void build_monster_area(Game game);
void animate(void (*renderFN)(Game game, int i),Game game,int current_anim, int num_of_sprites);


#endif