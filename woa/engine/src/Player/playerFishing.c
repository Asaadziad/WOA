#include "../../../headers/playerFishing.h"
#include "../../../headers/logger.h"

static void levelUp(Player p){
    if(p->current_xp > p->level*69){
        p->level++;
        p->current_xp = 0;
    }
}

void startFishing(TASK task,Player p){
    LOG("You started fishing!");
    p->current_xp += 69;
    levelUp(p);
    markTaskFinished(task);
}