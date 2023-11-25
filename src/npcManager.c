#include "npcManager.h"
#include "DS/list.h"
#include "stdlib.h"
#include "npc.h"
#include "CollisionDetection.h"

struct npcmanager_t {
    List npc_list;
};

static void npcDestroyPtr(void* elem){
    destroyNPC((NPC)elem);
}

NpcManager initNPCManager(){
    NpcManager manager = (NpcManager)malloc(sizeof(*manager));
    if(!manager) return NULL;
    manager->npc_list = listCreate(npcDestroyPtr,NULL,NULL);
    return manager;
}


// manually setting up for the moment
void setupNPCs(NpcManager manager){
    NPC npc = createNPC(500,200,60,60);
    listInsert(manager->npc_list,npc);
}

void renderNPCs(NpcManager manager,TextureManager texture_manager,SDL_Renderer* renderer, SDL_Rect camera){
    Node current = getHead(manager->npc_list);
    if(!current) return;
    for(int i = 0; i < getListSize(manager->npc_list);i++){
        NPC tmp = getNodeData(current);
        drawNPC(texture_manager,renderer,tmp,camera);
        current = getNextNode(current);
    }
}

void updateNPCs(NpcManager manager){
    Node current = getHead(manager->npc_list);
    if(!current) return;
    for(int i = 0; i < getListSize(manager->npc_list);i++){
        NPC tmp = getNodeData(current);
        updateNPC(tmp);
        current = getNextNode(current);
    }
}

void checkPlayerCollisionWithNPCs(NpcManager manager,Player p){
    Node current = getHead(manager->npc_list);
    for(int i = 0;i < getListSize(manager->npc_list);i++){
        NPC tmp  = getNodeData(current);
        SDL_Rect rect = getRect(tmp);
        if(checkCollision(p,rect) && ( p->invincible_frames == 0)){
            p->hp -= 1;
            p->invincible_frames = 60;
        }
        current = getNextNode(current);
    }
}

void destroyNPCManager(NpcManager manager){
    if(!manager) return;
    listDestroy(manager->npc_list);
    free(manager);
}