#include "logic.h"
#include "rendering.h"

void moveCharacter(Game game,int x, int y){
    game->players[0]->x = x;
    game->players[0]->y = y;
}