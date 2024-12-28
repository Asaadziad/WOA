#include "SDL2/SDL.h"

#include "headers/movementHandler.h"
#include "headers/player.h"
#include "headers/common.h"
#include "headers/CollisionDetection.h"

void handlePlayerMovement(Player p, MovementType m_type){
    #define P_VEL 5
    p->current_frame++;
    switch(m_type){
        case MOVE_UP:
        p->vel.y = -P_VEL;
        if(p->position.y < 0) p->vel.y = 0;
        break;
        
        case MOVE_DOWN:
        if(p->position.y >= (TILE_HEIGHT * MAX_WORLD_ROWS)) p->vel.y = 0;


        p->vel.y = P_VEL;
        break;
  
        case MOVE_RIGHT:

        if(p->position.x + TILE_WIDTH >= (TILE_WIDTH * MAX_WORLD_COLS)) p->vel.x = 0;

        p->vel.x =  P_VEL;
        break;

        case MOVE_LEFT:
        p->vel.x = -P_VEL;
        if(p->position.x < 0) {
            p->vel.x = 0;
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
