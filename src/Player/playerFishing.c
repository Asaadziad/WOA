#include "playerFishing.h"

static void levelUp(Player p){
    if(p->current_xp > p->level*69){
        p->level++;
        p->current_xp = 0;
    }
}

void startFishing(Player p){
    p->current_xp += 69;
    levelUp(p);
}