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

void handleLogic(Game game) {
    initPlayerMovement(game->players);
}

static void moveCharacterTo(Player p, int x,int y){
    int currentX = p->x + p->width/2;
    int currentY = p->y + p->height/2;

    if((currentX) < x){
        p->x += p->p_vel;
    } else if((currentX) > x){
        p->x -= p->p_vel;
    }

    if((currentY) < y){
        p->y += p->p_vel;
    } else if((currentY) > y){
        p->y -= p->p_vel;
    }

    if(currentX == x && currentY == y){
        p->state = STANDING_STATE;
    }
}

void moveCharacter(Player p){
    if(p->isMoving){
        p->state = WALKING_STATE;
        moveCharacterTo(p,p->walk_to_x,p->walk_to_y);
    } else {
        p->state = STANDING_STATE;
    }
}
