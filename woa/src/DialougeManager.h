#ifndef DIALOUGE_MANAGER_H
#define DIALOUGE_MANAGER_H

#include "TextureManager.h"
#include "Dialouge.h"


typedef struct dialougem_t* DialougeManager;


DialougeManager initDialougeManager();
void setupDialouges(DialougeManager manager,const char* file_path);
void renderDialouge(DialougeManager manager,TextureManager texture_manager,SDL_Renderer* renderer,int dialouge_id);
void sendDialouge(int dialouge_id);
void destroyDialogeManager(DialougeManager manager);

#endif
