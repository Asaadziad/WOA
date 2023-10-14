#include "player.h"
#include "stdlib.h"


Player initPlayer(int x,int y){
    Player new_p = (Player)malloc(sizeof(*new_p));
    if(!new_p) return NULL;
    new_p->x = x;
    new_p->y = y;
    return new_p;
}
