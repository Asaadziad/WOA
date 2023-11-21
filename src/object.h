#ifndef OBJECT_H
#define OBJECT_H

#include "SDL2/SDL.h"
#include "TextureManager.h"

typedef enum {
    FISHING_SPOT,
    TREE_OBJECT,
} ObjectType;


typedef struct object_t* OBJECT;


OBJECT createObject(int height, int width, int x, int y,ObjectType type);
void destroyObject(OBJECT obj);
void objectDraw(TextureManager manager,OBJECT obj,SDL_Renderer* renderer,SDL_Rect camera);
void printObject(OBJECT obj);

void objectUpdate(OBJECT obj);
ObjectType objectGetType(OBJECT obj);
SDL_Rect objectGetRect(OBJECT obj);

#endif