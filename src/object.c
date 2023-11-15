#include "object.h"



struct object_t {
    ObjectType type;
    SDL_Rect src;
};

OBJECT createObject(int height, int width, int x, int y,ObjectType type){
    OBJECT obj = (OBJECT)malloc(sizeof(*obj));
    if(!obj) return NULL;
    SDL_Rect src;
    src.x = x;
    src.y = y;
    src.h = height;
    src.w = width;
    obj->src = src;
    obj->type = type;
    return obj;
}

void objectDraw(TextureManager manager,OBJECT obj,SDL_Renderer* renderer){
    switch(obj->type){
        case TREE_OBJECT:
            drawFrame(manager,TREE_TEXTURE,obj->src.x,obj->src.y,obj->src.w,obj->src.h,50,50,1,0,renderer,SDL_FLIP_NONE);
        break;
        default:break;
    }
}

void objectUpdate(OBJECT obj){
    switch (obj->type)
    {
    case TREE_OBJECT:
        
        break;
    
    default:
        break;
    }
}

void destroyObject(OBJECT obj){
    free(obj);
}

ObjectType objectGetType(OBJECT obj){
    return obj->type;
}
SDL_Rect objectGetRect(OBJECT obj){
    return obj->src;
}
