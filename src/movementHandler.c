#include "SDL2/SDL.h"

#include "movementHandler.h"
#include "player.h"


static bool checkXout(int x){
    if(x <= 0 || x >= 800) return true;
    return false;
}
static bool checkYout(int y){
    if(y <= 0 || y >= 600) return true;
    return false;
}
// Entity can be Player/Monster
void handleMovement(EntityType type,void* Entity){
    switch (type)
    {
    case PLAYER_TYPE:
        Player p = (Player)Entity;
        if(!p->isMoving) break;
        if(checkXout(p->x + p->width) || checkXout(p->x)){
            p->vel.x *= -1;
        }
        if(checkYout(p->y + p->height) || checkYout(p->y)){
            p->vel.y *= -1;
        }
        p->x += p->vel.x;
        p->y += p->vel.y;
        break;
    case MONSTER_TYPE:
    break;
    default:
        break;
    }
}

void handlePlayerMovement(Player p, MovementType m_type){
    
    switch(m_type){
        case MOVE_UP:
        p->y -= checkYout(p->y) ? 0 : p->vel.y;
        break;
        
        case MOVE_DOWN:
        p->y += checkYout(p->y + p->height) ? 0 : p->vel.y;
        break;
  
        case MOVE_RIGHT:
        p->x += checkXout(p->x + p->width) ? 0 : p->vel.x;
        break;

        case MOVE_LEFT:
        p->x -= checkXout(p->x) ? 0 : p->vel.x;
        break;
 
        default:
        break;
    }
}