#include "stdlib.h"

#include "entity.h"

Entity initEntity(EntityType type,unsigned int height, unsigned int width){
    Entity e = (Entity)malloc(sizeof(*e));
    if(!e) return NULL;
    Vector2f pos = {0,0};
    e->position = pos;
    e->velocity = pos;
    e->height = height;
    e->width = width;
    e->type = type;
    return e;
}