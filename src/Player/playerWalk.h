#ifndef PLAYER_WALK_H
#define PLAYER_WALK_H

#include "../game.h"
#include "../player.h"
#include "../object.h"

void playerWalkTo(Game game, Player p, int x, int y);
void playerWalkToObject(Game game,Player p, OBJECT obj);

#endif