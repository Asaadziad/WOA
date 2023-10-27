#include "logic.h"
#include "rendering.h"
#include "entity.h"
#include "movementHandler.h"

#define CHECK_BOUNDARYX(x) ((x > 0) && (x < SCREEN_WIDTH))
#define CHECK_BOUNDARYY(y) ((y > 0) && (y < SCREEN_HEIGHT))
#define CHECK_BOUNDARY(x,y) ((CHECK_BOUNDARYX(x)) && (CHECK_BOUNDARYY(y)))


void handleLogic(Game game,uint32_t time) {
    //initPlayerMovement(game->players);
    handleMovement(PLAYER_TYPE,game->players[0],time);
   // handleTilesMovement(game->players[0],game->players[0]->tile_list);
}


void moveCharacter(Player p){

}

void shootTile(Player p){
    
}
