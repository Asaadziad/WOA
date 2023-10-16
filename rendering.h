#ifndef RENDERING_H
#define RENDERING_H

#include "SDL2/SDL.h"
#include "game.h"


void render_character(SDL_Renderer* renderer,Game game,int x,int y,int camX,int camY);
void render_fence(Game game);
void render_monster(Game game);


#endif