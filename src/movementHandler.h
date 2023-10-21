#ifndef MOVEMENT_HANDLER_H
#define MOVEMENT_HANDLER_H

#include "entity.h"
#include "player.h"

typedef enum {
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT
} MovementType;

void handleMovement(EntityType type,void* Entity);
void handlePlayerMovement(Player p, MovementType m_type);
void handleTileMovement(Player p ,Tile t);

#endif