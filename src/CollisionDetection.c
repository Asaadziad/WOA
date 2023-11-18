#include "CollisionDetection.h"

// Checks collision with a certain rectangle
bool checkCollision(Player p, SDL_Rect dst){
    SDL_Rect src;
    src.x = p->position.x + 10;
    src.y = p->position.y + 10;
    src.h = p->height - 10;
    src.w = p->width - 10;
    if(src.x + src.w >= dst.x && (src.x < dst.x) && (src.y >= dst.y && src.y <= dst.y + dst.h)){
        p->position.x = dst.x - p->width;
    }
    if((src.x + src.w > dst.x) 
    && (src.x < dst.x + dst.w)
    && (src.y + src.h > dst.y) 
    && (src.y < dst.y + dst.h)){

        return true;
    }
    return false;
}
