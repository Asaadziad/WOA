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


void moveCharacter(Player p){

}
