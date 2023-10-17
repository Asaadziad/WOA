#include "player.h"
#include "stdlib.h"


Player initPlayer(int x,int y){
    Player new_p = (Player)malloc(sizeof(*new_p));
    if(!new_p) return NULL;
    new_p->x = x;
    new_p->y = y;
    new_p->walk_to_x = x;
    new_p->walk_to_y = y;
    new_p->state = STANDING_STATE;
    new_p->walking_frames = 3;
    new_p->current_frame = 0;
    new_p->p_vel = 1;
    new_p->height = 384;
    new_p->width = 144;
    new_p->isMoving = false;
    return new_p;
}
