#ifndef NPC_MANAGER_H
#define NPC_MANAGER_H

#include "SDL2/SDL.h"
#include "TextureManager.h"
#include "player.h"

typedef struct npcmanager_t* NpcManager;

NpcManager initNPCManager();

void setupNPCs(NpcManager manager);
void renderNPCs(NpcManager manager,TextureManager texture_manager,SDL_Renderer* renderer,SDL_Rect camera);
void updateNPCs(NpcManager manager);

void checkPlayerCollisionWithNPCs(NpcManager manager,Player p);

#endif