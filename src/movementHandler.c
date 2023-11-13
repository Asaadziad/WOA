#include "SDL2/SDL.h"

#include "movementHandler.h"
#include "player.h"
#include "common.h"

static bool checkXout(int x){
    
    return false;
}
static bool checkYout(int y){

    return false;
}

void handlePlayerMovement(Player p, MovementType m_type){
    
    fprintf(stderr,"COORD-X: %f COORD-Y: %f\n",p->position.x,p->position.y);
    switch(m_type){
        case MOVE_UP:
        p->position.y -= checkYout(p->position.y) ? 0 : p->vel.y;
        if(p->position.y < 0) {
            p->position.y = 0;
            return;
        }
        break;
        
        case MOVE_DOWN:
        if(p->position.y >= WORLD_HEIGHT) return;
        p->position.y += checkYout(p->position.y + p->height) ? 0 : p->vel.y;
        break;
  
        case MOVE_RIGHT:
        if(p->position.x + TILE_WIDTH >= WORLD_WIDTH) return;
        p->position.x += checkXout(p->position.x + p->width) ? 0 : p->vel.x;
        break;

        case MOVE_LEFT:
        p->position.x -= checkXout(p->position.x) ? 0 : p->vel.x ;
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