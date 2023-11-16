#include "CollisionDetection.h"

// Checks collision with a certain rectangle
bool checkCollision(Player p, SDL_Rect dst){
    SDL_Rect src;
    src.x = p->position.x;
    src.y = p->position.y;
    src.h = p->height;
    src.w = p->width;
    if((src.x + src.w > dst.x) && (src.x < dst.x + dst.w) && (src.y + src.h > dst.y) && (src.y < dst.y + dst.h)){
        return true;
    }
    return false;
}
