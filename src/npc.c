#include "npc.h"
#include "stdlib.h"
#include "TextureManager.h"
#include "tile.h"
#include "CollisionDetection.h"

struct npc_t {
    int x;
    int y;
    int width;
    int height;
    int current_frame;
    
    NpcDirection direction;
    int action_locker;
    int hp;
    SDL_Rect attack_range;
    SDL_Rect aggro_range;
    SDL_Rect enemey_walk_target;
    int invincible_frames;
    bool isAttacking;
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
    attack_range.x = x - 16;
    attack_range.y = y - 16;
    attack_range.h = height + 16*2;
    attack_range.w = width + 16*2;
    SDL_Rect aggro_range;
    aggro_range.x = x - 32;
    aggro_range.y = y - 32;
    aggro_range.h = height + 32*2;
    aggro_range.w = width + 32*2;
    n->attack_range = attack_range;
    n->aggro_range = aggro_range;
    n->direction = NPC_NORTH;
    n->isAttacking = false;
    return n;
}

void destroyNPC(NPC npc){
    free(npc);
}

void drawNPC(TextureManager manager,SDL_Renderer* renderer,NPC npc,SDL_Rect camera){
    drawRect(npc->attack_range.x - camera.x,npc->attack_range.y  - camera.y,npc->attack_range.h,npc->attack_range.w,(SDL_Color){255,0,0},false,0,renderer);
    drawRect(npc->aggro_range.x - camera.x,npc->aggro_range.y  - camera.y,npc->aggro_range.h,npc->aggro_range.w,(SDL_Color){0,0,255},false,0,renderer);

    drawRect(npc->x - camera.x,npc->y - camera.y - 20,10,npc->width,(SDL_Color){0,255,0},true,((float)npc->hp/100)*npc->width,renderer);

    if(npc->direction == NPC_WEST){
        drawFrame(manager,NPC_TEXTURE,npc->x - camera.x,npc->y - camera.y,TILE_WIDTH,TILE_WIDTH,TILE_WIDTH,TILE_WIDTH,2,npc->current_frame,renderer,SDL_FLIP_HORIZONTAL);

    } else if(npc->direction == NPC_EAST) {
        drawFrame(manager,NPC_TEXTURE,npc->x - camera.x,npc->y - camera.y,TILE_WIDTH,TILE_WIDTH,TILE_WIDTH,TILE_WIDTH,2,npc->current_frame,renderer,SDL_FLIP_NONE);
    } else if(npc->direction == NPC_NORTH){
        drawFrame(manager,NPC_TEXTURE,npc->x - camera.x,npc->y - camera.y,TILE_WIDTH,TILE_WIDTH,TILE_WIDTH,TILE_WIDTH,3,npc->current_frame,renderer,SDL_FLIP_NONE);
    } else if(npc->direction == NPC_SOUTH){
        drawFrame(manager,NPC_TEXTURE,npc->x - camera.x,npc->y - camera.y,TILE_WIDTH,TILE_WIDTH,TILE_WIDTH,TILE_WIDTH,1,npc->current_frame,renderer,SDL_FLIP_NONE);

    }
}

static void artificalWalk(NPC npc){
    
    npc->action_locker++;
    if(npc->action_locker == 60){

    int random_ = (rand()%100) + 1;
    if(random_ <= 25){
        npc->direction = NPC_NORTH;
    } else if(random_ > 25 && random_ <= 50){
            npc->direction = NPC_SOUTH;
    } else if(random_ > 50 && random_ <= 75) {
            npc->direction = NPC_WEST;
    } else if(random_ > 75 && random_ <= 100){
            npc->direction = NPC_EAST;
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

static void updateNPCAttackRanger(NPC npc){
    SDL_Rect attack_range;
    attack_range.x = npc->x - 16;
    attack_range.y = npc->y - 16;
    attack_range.h = npc->height + 16*2;
    attack_range.w = npc->width + 16*2;
    npc->attack_range = attack_range;
    SDL_Rect aggro_range;
    aggro_range.x = npc->x - 32;
    aggro_range.y = npc->y - 32;
    aggro_range.h = npc->height + 32*2;
    aggro_range.w = npc->width + 32*2;
    npc->aggro_range = aggro_range;
}

void updateNPC(NPC npc){

    if(!npc->isAttacking){
    npc->current_frame = (int)(SDL_GetTicks()/100) % 6;
    // every 2 seconds change position
        artificalWalk(npc);
        
        switch(npc->direction){
            case NPC_NORTH:
                npc->y -= NPC_VEL;
            break;
            case NPC_SOUTH:
                npc->y += NPC_VEL;
            break;
            case NPC_EAST:
                npc->x += NPC_VEL;
            break;
            case NPC_WEST:
                npc->x -= NPC_VEL;
            break;
        }
    } else {
        npc->direction = NPC_WEST;
        npc->current_frame = 0;
    }
    if(npc->invincible_frames > 0){
        npc->invincible_frames--;
    }
    if(npc->hp < 0){
        npc->hp = 0;
    }
    updateNPCAttackRanger(npc);
}

void npcAttackPlayer(NPC npc,Player p){
    // walk to the player where the player collides with attack range of npc.
    // start attacking (npcisattack = true) - until npc is dead (for now)
    npc->isAttacking = true;
    if(p->invincible_frames > 0) return;
    p->hp -= 5;
    p->invincible_frames = 30;
}

bool isNpcInvincible(NPC npc){
    return (npc->invincible_frames > 0);
}

void setNpcInvincible(NPC npc){
    npc->invincible_frames = 30;
}

void setNpcAttacking(NPC npc, bool value){
    npc->isAttacking = value;
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

SDL_Rect getNpcAggroRange(NPC npc){
    return npc->aggro_range;
}