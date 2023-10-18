#include "SDL2/SDL.h"

#include "movementHandler.h"
#include "player.h"

#define CHECK_AXIS(x,w) ((x == 0) || (x == w))

// Entity can be Player/Monster
void randomMovement(EntityType type,void* Entity){
    switch (type)
    {
    case PLAYER_TYPE:
        Player p = (Player)Entity;
        if(!CHECK_AXIS(p->x + p->width,800) || !CHECK_AXIS(p->y + p->height,600)){
            p->vel *= -1;
        } 

        break;
    case MONSTER_TYPE:
    break;
    default:
        break;
    }
}