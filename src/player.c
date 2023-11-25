#include "player.h"
#include "stdlib.h"
#include "memory.h"
#include "common.h"

#define TILE_STARTER 10

Player initPlayer(int x,int y,int width,int height){
    Player new_p = (Player)malloc(sizeof(*new_p));
    if(!new_p) return NULL;
    new_p->current_frame = 1;
    new_p->hp = 100;
    Vector2f pos = {x,y};
    new_p->position = pos;
    new_p->screenX = SCREEN_WIDTH/2 - (TILE_WIDTH/2);
    new_p->screenY = SCREEN_HEIGHT/2 - (TILE_HEIGHT/2);
    new_p->width = width;
    new_p->height = height;
    Vector2f vel = {10,10};
    new_p->vel = vel;
    new_p->level = 0;
    new_p->current_xp = 0;
    new_p->canMoveDown = true;
    new_p->canMoveUp = true;
    new_p->canMoveLeft = true;
    new_p->canMoveRight = true;
    new_p->isInDialouge = false;
    new_p->isInInventory = false;
    new_p->inventory_objects = (ObjectType*)malloc(sizeof(*new_p->inventory_objects) * INVENTORY_SLOTS);
    if(!new_p->inventory_objects) return NULL;
    new_p->current_slot = 0;
    new_p->invincible_frames = 0;
    new_p->isAttacking = false;
    new_p->attacking_frames = 0;
    return new_p;
}

void playerDraw(TextureManager manager,Player p,SDL_Renderer* renderer,SDL_Rect camera){
    drawFrame(manager,PLAYER_TEXTURE,p->position.x - camera.x,p->position.y - camera.y,32,32,60,60,(p->current_frame/3) + 1,p->current_frame % 3,renderer,SDL_FLIP_NONE);
    
}

void playerAttack(Player p){
    p->isAttacking = true;
}

void playerUpdate(Player p,SDL_Rect camera){
    if(p->current_frame >= 9 && (!p->isAttacking)){
        p->current_frame = 0;
    }
    if(p->isAttacking){
        p->current_frame = 10 + (p->attacking_frames%3); // 10 11 12
        p->attacking_frames++;
    }
    if(p->hp <= 0){
        p->hp = 0;
    }
    if(p->invincible_frames > 0){
        p->invincible_frames--;
    }
    if(p->attacking_frames >= 3){
        p->attacking_frames = 0;
        p->isAttacking = false;
    }
}


void destroyPlayer(Player p){
    free(p);
}

