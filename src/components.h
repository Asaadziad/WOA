#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "TextureManager.h"
#include "SDL2/SDL.h"
#include "stdbool.h"

typedef enum {
    INVENTORY_COMPONENT,
} ComponentType;

typedef struct component_t* COMPONENT;

COMPONENT createComponent(int x,int y,int width,int height,ComponentType type,bool isHoverable,bool isInteractable);
void destroyComponent(COMPONENT c);

void componentDraw(TextureManager manager,COMPONENT c,SDL_Renderer* renderer);
bool componentsCompare(COMPONENT c1,COMPONENT c2);

#endif