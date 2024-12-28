#ifndef PLAYER_WALK_H
#define PLAYER_WALK_H

#include "player.h"
#include "object.h"
#include "task.h"

void playerWalkTo(TASK task,Player p, int x, int y);
void playerWalkToObject(TASK task,Player p, OBJECT obj);

#endif