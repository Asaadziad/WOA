#include "../headers/components.h"
#include "../headers/common.h"

struct component_t {
    int screenX;
    int screenY;
    int width;
    int height;
//    TexType texture_type;
    ComponentType type;
    bool isHoverable;
    bool isInteractable;    
};


COMPONENT createComponent(int x,int y,int width,int height,ComponentType type,bool isHoverable,bool isInteractable){
    COMPONENT c = (COMPONENT)malloc(sizeof(*c));
    if(!c) return NULL;
    c->screenX = x;
    c->screenY = y;
    c->width = width;
    c->height = height;
    c->type = type;
    c->isHoverable = isHoverable;
    c->isInteractable = isInteractable;
    return c;
}

void componentDraw(TextureManager manager,COMPONENT c,SDL_Renderer* renderer){
    //draw(manager,c->texture_type,c->screenX,c->screenY,c->width,c->height,renderer,SDL_FLIP_NONE);
}

bool componentsCompare(COMPONENT c1,COMPONENT c2){
    if(c1->type == c2->type) return true;
    return false;
}

void destroyComponent(COMPONENT c){
    free(c);
}
