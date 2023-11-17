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

void objectDraw(TextureManager manager,OBJECT obj,SDL_Renderer* renderer,SDL_Rect camera){
    if(!obj) {
        return;
    }
    int screenX = obj->src.x - camera.x;
    int screenY = obj->src.y - camera.y;
    switch(obj->type){
        case TREE_OBJECT:
            drawFrame(manager,TREE_TEXTURE,screenX,screenY,32,32,obj->src.w,obj->src.h,1,0,renderer,SDL_FLIP_NONE);
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
