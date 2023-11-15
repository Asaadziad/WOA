#include "CollisionDetection.h"


bool checkCollision(Player p, SDL_Rect dst){
    if(p->position.x + p->width >= dst.x && p->position.y >= dst.y && p->position.y <= dst.y + dst.h) return true;
    return false;
}