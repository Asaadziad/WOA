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

void destroyObject(OBJECT obj){
    free(obj);
}

ObjectType objectGetType(OBJECT obj){
    return obj->type;
}
SDL_Rect objectGetRect(OBJECT obj){
    return obj->src;
}
