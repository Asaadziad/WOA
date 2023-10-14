#ifndef RENDERING_H
#define RENDERING_H

#include "SDL2/SDL.h"
#include "game.h"


void render_character(SDL_Renderer* renderer,Game game,int x,int y);
void render_game(Game game);

#endif