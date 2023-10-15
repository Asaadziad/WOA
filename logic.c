#include "logic.h"
#include "rendering.h"

#define CHECK_BOUNDARYX(x) ((x > 0) && (x < SCREEN_WIDTH))
#define CHECK_BOUNDARYY(y) ((y > 0) && (y < SCREEN_HEIGHT))
#define CHECK_BOUNDARY(x,y) ((CHECK_BOUNDARYX(x)) && (CHECK_BOUNDARYY(y)))

static void initPlayerMovement(Player* players){
    for(int i = 0; i < PLAYERS_COUNT;i++){
        moveCharacter(players[i]);
    }
}

void initLogic(Game game) {
    initPlayerMovement(game->players);
}

static void moveCharacterTo(Player p, int x,int y){
    if(p->x < x){
        p->x += p->p_vel;
    } else if(p->x > x){
        p->x -= p->p_vel;
    }

    if(p->y < y){
        p->y += p->p_vel;
    } else if(p->y > y){
        p->y -= p->p_vel;
    }
}

void moveCharacter(Player p){
    if(p->walk_to_x != p->x || p->walk_to_y != p->y){
        moveCharacterTo(p,p->walk_to_x,p->walk_to_y);
        p->state = WALKING_STATE;
    } else {
        p->state = STANDING_STATE;
    }
}
