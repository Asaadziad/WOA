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
    int hp;
    SDL_Rect attack_range;
    int invincible_frames;
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
    n->hp = 69;
    n->invincible_frames = 0;
    SDL_Rect attack_range;
    attack_range.x = x - 64;
    attack_range.y = y - 64;
    attack_range.h = height + 64*2;
    attack_range.w = width + 64*2;
    n->attack_range = attack_range;
    return n;
}

void destroyNPC(NPC npc){
    free(npc);
}

void drawNPC(TextureManager manager,SDL_Renderer* renderer,NPC npc,SDL_Rect camera){
    drawRect(npc->x - camera.x,npc->y - camera.y - 20,10,npc->width,(SDL_Color){0,255,0},true,((float)npc->hp/100)*npc->width,renderer);
    drawFrame(manager,NPC_TEXTURE,npc->x - camera.x,npc->y - camera.y,32,32,64,64,1,npc->current_frame,renderer,SDL_FLIP_NONE);
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

void setNPCHp(NPC npc,int new_hp){
    npc->hp = new_hp;
}

int getNPCHp(NPC npc){
    if(!npc) return 0;
    return npc->hp;
}

void updateNPC(NPC npc){
    npc->current_frame = (int)(SDL_GetTicks()/100) % 6;

    // every 2 seconds change position
    artificalWalk(npc);
    if(npc->invincible_frames > 0){
        npc->invincible_frames--;
    }
    if(npc->hp < 0){
        npc->hp = 0;
    }
}

bool isNpcInvincible(NPC npc){
    return (npc->invincible_frames > 0);
}

void setNpcInvincible(NPC npc){
    npc->invincible_frames = 30;
}


SDL_Rect getRect(NPC npc){
    SDL_Rect rect;
    rect.x = npc->x;
    rect.y = npc->y;
    rect.h = npc->height;
    rect.w = npc->width;
    return rect;    
}

SDL_Rect getNpcAttackRange(NPC npc){
    return npc->attack_range;
}