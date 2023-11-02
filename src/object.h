#ifndef OBJECT_H
#define OBJECT_H

#include "SDL2/SDL.h"

typedef enum {
    FISHING_SPOT,
} ObjectType;


typedef struct object_t* OBJECT;


OBJECT createObject(int height, int width, int x, int y,ObjectType type);
void destroyObject(OBJECT obj);

ObjectType objectGetType(OBJECT obj);
SDL_Rect objectGetRect(OBJECT obj);

#endif