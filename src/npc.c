#include "npc.h"
#include "stdlib.h"
#include "TextureManager.h"

struct npc_t {
    int x;
    int y;
    int width;
    int height;
    int current_frame;
    int action_locker;
};

NPC createNPC(int x, int y, int width,int height){
    NPC n = (NPC)malloc(sizeof(*n));
    if(!n) return NULL;
    n->x = x;
    n->y = y;
    n->width = width;
    n->height = height;
    n->current_frame = 0;
    n->action_locker = 0;
    return n;
}

void destroyNPC(NPC npc){
    free(npc);
}

void drawNPC(TextureManager manager,SDL_Renderer* renderer,NPC npc,SDL_Rect camera){
    drawFrame(manager,NPC_TEXTURE,npc->x - camera.x,npc->y - camera.y,32,32,60,60,1,npc->current_frame,renderer,SDL_FLIP_NONE);
}

static void artificalWalk(NPC npc){
    #define NPC_VEL 10
    npc->action_locker++;
    if(npc->action_locker == 120){

    int random_ = rand()%4;
    switch(random_){
        case 0:
            npc->x += NPC_VEL;
        break;
        case 1:
            npc->x -= NPC_VEL;
        break;
        case 2:
            npc->y += NPC_VEL;
        break;
        case 3:
            npc->y -= NPC_VEL;
        break;
    
    }
    npc->action_locker = 0;
    }
}

void updateNPC(NPC npc){
    npc->current_frame = (int)(SDL_GetTicks()/100) % 6;

    // every 2 seconds change position
    artificalWalk(npc);
}

SDL_Rect getRect(NPC npc){
    SDL_Rect rect;
    rect.x = npc->x;
    rect.y = npc->y;
    rect.h = npc->height;
    rect.w = npc->width;
    return rect;    
}