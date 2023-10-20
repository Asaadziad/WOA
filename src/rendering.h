#ifndef RENDERING_H
#define RENDERING_H

#include "SDL2/SDL.h"
#include "game.h"
#include "tile.h"

void renderPlayer(Game game,Player p);
void renderTile(Game game,int x);

#endif