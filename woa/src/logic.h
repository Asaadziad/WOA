#ifndef LOGIC_H
#define LOGIC_H
#include "game.h"
#include "player.h"

void handleLogic(Game game, uint32_t time);
void moveCharacter(Player p);
void shootTile(Player p);

#endif
