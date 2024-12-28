#include "stdlib.h"

#include "headers/player.h"
#include "headers/memory.h"
#include "headers/common.h"

#define TILE_STARTER 10

Player initPlayer(int x,int y,int width,int height){
    Player new_p = (Player)malloc(sizeof(*new_p));
    if(!new_p) return NULL;
    new_p->current_frame = 1;
    new_p->frame_row = 3;
    new_p->hp = 100;
    Vector2f pos = {x,y};
    new_p->position = pos;
    new_p->screenX = SCREEN_WIDTH/2 - (TILE_WIDTH/2);
    new_p->screenY = SCREEN_HEIGHT/2 - (TILE_HEIGHT/2);
    new_p->width = width;
    new_p->height = height;
    Vector2f vel = {0,0};
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
    if(p->isAttacking){
    drawFrame(manager,"character.png",p->position.x - camera.x,p->position.y - camera.y,TILE_WIDTH + 32,TILE_HEIGHT,TILE_WIDTH + 32,TILE_HEIGHT,p->frame_row,p->current_frame,renderer,SDL_FLIP_NONE);

    } else {
    drawFrame(manager,"character.png",p->position.x - camera.x,p->position.y - camera.y,TILE_WIDTH,TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT,p->frame_row,p->current_frame,renderer,SDL_FLIP_NONE);

    }   
}

bool playerCheckInventory(Player p,ObjectType item_type){
    int inv_size = p->current_slot;
    for(int i = 0;i<inv_size;i++){
        if(p->inventory_objects[i] == item_type){
            return true;
        }
    }
    return false;
}

void playerAttack(Player p){
    p->isAttacking = true;
}

typedef enum {
    NORMAL_STATE,
    ATTACK_STATE,
} AnimateState;

static void animate(Player p,AnimateState state){
    switch(state){
        case NORMAL_STATE: // walking...
            if(playerCheckInventory(p,SWORD_OBJECT)){ // if the player has sword
                p->frame_row = 2;
            } else {
                p->frame_row = 3;
            }
        break;
        case ATTACK_STATE: // attack animation
            p->frame_row = 1;
        break;
    }
}

void playerUpdate(Player p,SDL_Rect camera){
    if(p->isAttacking){
        animate(p,ATTACK_STATE);
    } else {
        animate(p,NORMAL_STATE);

    }
    if(p->current_frame >= 5 && (!p->isAttacking)){
        p->current_frame = 0;
    }
    if(p->isAttacking){
        p->current_frame++;
        p->attacking_frames++;

        if(p->attacking_frames <= 5) {
            p->current_frame = 0;
        }
        if(p->attacking_frames > 5 && p->attacking_frames <= 25) {
            p->current_frame = 1;
            
        }
        if(p->attacking_frames > 25){
            p->attacking_frames = 0;
            p->isAttacking = false;
            p->current_frame = 0;
        }
    }
    if(p->hp <= 0){
        p->hp = 0;
    }
    if(p->invincible_frames > 0){
        p->invincible_frames--;
    }
   p->position.x += p->vel.x;
   p->position.y += p->vel.y;
}


void destroyPlayer(Player p){
    free(p);
}

