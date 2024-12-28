#ifndef OBJECT_H
#define OBJECT_H

#include "SDL2/SDL.h"
#include "TextureManager.h"

typedef enum {
    FISHING_SPOT,
    TREE_OBJECT,
    SWORD_OBJECT,
} ObjectType;


typedef struct object_t* OBJECT;


OBJECT createObject(int w, int h, int x, int y, ObjectType type);
#ifndef DEFAULCREATEOBJECT
#define CREATE_DEFAULT_OBJ(type) createObject(0,0,0,0,type)
#endif
void destroyObject(OBJECT obj);
void objectDraw(TextureManager manager,OBJECT obj,SDL_Renderer* renderer,SDL_Rect camera);
void printObject(OBJECT obj);
bool checkObjectsTypes(OBJECT obj1,OBJECT obj2);
void objectUpdate(OBJECT obj);



void setObjectFrame(OBJECT obj,int frame);
int getObjectFrame(OBJECT obj);
void setObjectRenderable(OBJECT obj, bool isRenderable);
ObjectType objectGetType(OBJECT obj);
SDL_Rect objectGetRect(OBJECT obj);
bool isObjectRenderable(OBJECT obj);

#endif
