#include "CollisionDetection.h"

// Checks collision with a certain rectangle
bool checkCollision(Player p, SDL_Rect dst,bool reposition){
    SDL_Rect src;
    src.x = p->position.x;
    src.y = p->position.y;
    src.h = p->height;
    src.w = p->width;
    if(reposition){
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

    }
    if(p->isAttacking){ // player is attacking then check the collision of the sword
        // the collision of the sword is a rect of  - w : (TILE_WIDTH + 32) - h : (TILE_HEIGHT)
        src.x += TILE_WIDTH;
        src.w = 32;
        src.h = TILE_HEIGHT;
        if(src.x + src.w >= dst.x && src.x < dst.x + dst.w && (src.y >= dst.y && src.y < dst.y + dst.h)){
            return true;
        }
        
        
    }
    if((src.x + src.w > dst.x) 
    && (src.x < dst.x + dst.w)
    && (src.y + src.h > dst.y) 
    && (src.y < dst.y + dst.h)){

        return true;
    }
    return false;
}
