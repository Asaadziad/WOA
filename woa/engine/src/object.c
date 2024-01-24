#include "../../headers/object.h"

#include "../../headers/tile.h"

struct object_t {
    ObjectType type;
    int object_frame;
    bool isRenderable;
    SDL_Rect src;
};

OBJECT createObject(int w, int h, int x, int y, ObjectType type){
    OBJECT obj = (OBJECT)malloc(sizeof(*obj));
    if(!obj) return NULL;
    SDL_Rect src;
    src.x = x;
    src.y = y;
    src.h = h;
    src.w = w; 
    obj->src = src;
    obj->type = type;
    obj->isRenderable = true;
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

      //TODO:: add better drawing to screen    
                  drawFrame(manager,"woodcutting.png",screenX,screenY,TILE_WIDTH,TILE_HEIGHT,obj->src.w,obj->src.h,1,0,renderer,SDL_FLIP_NONE);
        break;
        case SWORD_OBJECT:
        drawFrame(manager,"weapons.png",screenX,screenY,TILE_WIDTH,TILE_HEIGHT,obj->src.w,obj->src.h,1,0,renderer,SDL_FLIP_NONE);
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

bool checkObjectsTypes(OBJECT obj1,OBJECT obj2){
    return obj1->type == obj2->type;
}

void destroyObject(OBJECT obj){
    if(!obj) return;
    free(obj);
}

void printObject(OBJECT obj){
    if(!obj) return;
    fprintf(stderr,"%d %d %d %d %d\n",obj->type,obj->src.x,obj->src.y,obj->src.w,obj->src.w);
}

void setObjectRenderable(OBJECT obj, bool isRenderable){
    if(!obj) return;
    obj->isRenderable = isRenderable;
}

int getObjectFrame(OBJECT obj){
    return obj->object_frame;
}

void setObjectFrame(OBJECT obj,int frame){
    obj->object_frame = frame;
}

ObjectType objectGetType(OBJECT obj){
    return obj->type;
}
SDL_Rect objectGetRect(OBJECT obj){
    return obj->src;
}

bool isObjectRenderable(OBJECT obj){
    return obj->isRenderable;
}
