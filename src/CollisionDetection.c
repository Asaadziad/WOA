#include "CollisionDetection.h"

// Checks collision with a certain rectangle
bool checkCollision(Player p, SDL_Rect dst){
    SDL_Rect src;
    src.x = p->position.x;
    src.y = p->position.y;
    src.h = p->height;
    src.w = p->width;
    if(src.x + src.w >= dst.x && (src.x < dst.x) && (src.y >= dst.y && src.y <= dst.y + dst.h)){
        p->position.x = dst.x - p->width;
    }
    if(src.x <= dst.x + dst.w && src.x + src.w > dst.x + dst.w && (src.y >= dst.y && src.y <= dst.y + dst.h)){
        p->position.x = dst.x + dst.w;
    }
    if(src.y <= dst.y + dst.h && src.y + src.h > dst.y + dst.h && (src.x >= dst.x && src.x <= dst.x + dst.w)){
        p->position.y = dst.y + dst.h - 10;
    }
    if(src.y + src.h >= dst.y && src.y < dst.y && (src.x >= dst.x && src.x <= dst.x + dst.w)){
        p->position.y = dst.y - p->height;
    }
    if((src.x + src.w > dst.x) 
    && (src.x < dst.x + dst.w)
    && (src.y + src.h > dst.y) 
    && (src.y < dst.y + dst.h)){

        return true;
    }
    return false;
}
