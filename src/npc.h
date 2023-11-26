#ifndef NPC_H
#define NPC_H
#include "TextureManager.h"
#include "SDL2/SDL.h"

typedef struct npc_t* NPC;

NPC createNPC(int x, int y,int width,int height);
void destroyNPC(NPC npc);

void drawNPC(TextureManager manager,SDL_Renderer* renderer,NPC npc, SDL_Rect camera);
void updateNPC(NPC npc);
int getNPCHp(NPC npc);
void setNPCHp(NPC npc,int new_hp);
bool isNpcInvincible(NPC npc);
void setNpcInvincible(NPC npc);
SDL_Rect getRect(NPC npc);
SDL_Rect getNpcAttackRange(NPC npc);
#endif