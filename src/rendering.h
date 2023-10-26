#ifndef RENDERING_H
#define RENDERING_H

#include "SDL2/SDL.h"
#include "game.h"
#include "tile.h"
#include "label.h"

void renderPlayer(Game game,Player p);
void renderTile(Game game,Tile tile);
void renderLabel(Game game);
#endif