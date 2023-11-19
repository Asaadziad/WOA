#ifndef NPC_H
#define NPC_H
#include "TextureManager.h"
#include "SDL2/SDL.h"

typedef struct npc_t* NPC;

NPC createNPC(int x, int y,int width,int height);
void destroyNPC(NPC npc);

void drawNPC(TextureManager manager,SDL_Renderer* renderer,NPC npc, SDL_Rect camera);
void updateNPC(NPC npc);

SDL_Rect getRect(NPC npc);
#endif