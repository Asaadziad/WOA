#include "SDL2/SDL.h"

#include "movementHandler.h"
#include "player.h"
#include "common.h"
#include "CollisionDetection.h"

void handlePlayerMovement(Player p, MovementType m_type){

    p->current_frame++;
    switch(m_type){
        case MOVE_UP:

        p->position.y -=  p->vel.y;
        if(p->position.y < 0) {
            p->position.y = 0;
            return;
        }
        break;
        
        case MOVE_DOWN:
        if(p->position.y >= (TILE_HEIGHT * MAX_WORLD_ROWS)) return;


        p->position.y +=  p->vel.y;
        break;
  
        case MOVE_RIGHT:

        if(p->position.x + TILE_WIDTH >= (TILE_WIDTH * MAX_WORLD_COLS)) return;

        p->position.x +=  p->vel.x;
        break;

        case MOVE_LEFT:
        p->position.x -= p->vel.x;
        if(p->position.x < 0) {
            p->position.x = 0;
            return;
        }
        
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