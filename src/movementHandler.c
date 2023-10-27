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
void handleMovement(EntityType type,void* Entity,uint32_t time){
    switch (type)
    {
    case PLAYER_TYPE:
        Player p = (Player)Entity;
        if(!p->isMoving) break;
        if(checkXout(p->position.x + p->width) || checkXout(p->position.x)){
            p->vel.x *= -1;
        }
        if(checkYout(p->position.y + p->height) || checkYout(p->position.y)){
            p->vel.y *= -1;
        }
        p->position.x += p->vel.x * time;
        p->position.y += p->vel.y * time;
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
        p->position.y -= checkYout(p->position.y) ? 0 : p->vel.y;
        break;
        
        case MOVE_DOWN:
        p->position.y += checkYout(p->position.y + p->height) ? 0 : p->vel.y;
        break;
  
        case MOVE_RIGHT:
        p->position.x += checkXout(p->position.x + p->width) ? 0 : p->vel.x;
        break;

        case MOVE_LEFT:
        p->position.x -= checkXout(p->position.x) ? 0 : p->vel.x;
        break;
 
        default:
        break;
    }
}

/*void handleTilesMovement(Player p,List tiles_list){
    if(!tiles_list) return;
    Node current = tiles_list->head;
    if(!current) return;
    while(current != NULL){
        int current_x = current->tile->current_position.x;
        int current_y = current->tile->current_position.y;
        if(checkXout(current_x) || checkXout(current_x + TILE_WIDTH)){
            removeHead(tiles_list);
            break;
        }
        if(checkYout(current_y) || checkYout(current_y + TILE_HEIGHT)){
            removeHead(tiles_list);
            break;
        }
        current->tile->current_position.x += current->tile->velocity.x;
        current->tile->current_position.y += current->tile->velocity.y;
        current = current->next;
    }
}*/