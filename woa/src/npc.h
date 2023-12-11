#ifndef NPC_H
#define NPC_H
#include "TextureManager.h"
#include "SDL2/SDL.h"
#include "player.h"

#define NPC_VEL 1

typedef enum {
    NPC_NORTH,
    NPC_SOUTH,
    NPC_WEST,
    NPC_EAST,
} NpcDirection;

typedef struct npc_t* NPC;

NPC createNPC(int x, int y,int width,int height);
void destroyNPC(NPC npc);

void drawNPC(TextureManager manager,SDL_Renderer* renderer,NPC npc, SDL_Rect camera);
void updateNPC(NPC npc);

void npcAttackPlayer(NPC npc,Player p);
int getNPCHp(NPC npc);
void setNPCHp(NPC npc,int new_hp);
bool isNpcInvincible(NPC npc);
void setNpcInvincible(NPC npc);
void setNpcAttacking(NPC npc, bool value);

SDL_Rect getRect(NPC npc);
SDL_Rect getNpcAttackRange(NPC npc);
SDL_Rect getNpcAggroRange(NPC npc);
#endif