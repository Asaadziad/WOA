#ifndef ENTITY_H
#define ENTITY_H

#include "vector.h"

typedef enum {
    PLAYER_TYPE,
    MONSTER_TYPE,
} EntityType;

typedef struct {
    Vector2f position;
    Vector2f velocity;
    unsigned int height;
    unsigned int width;
    EntityType type;
} *Entity;

Entity initEntity(EntityType type,unsigned int height, unsigned int width);

#endif