#ifndef DIALOUGE_MANAGER_H
#define DIALOUGE_MANAGER_H

#include "Dialouge.h"
#include "texture.h"

#include "SDL2/SDL_ttf.h"

typedef struct dialougem_t* DialougeManager;


DialougeManager initDialougeManager();
void destroyDialogeManager(DialougeManager manager);

// Dialouge actions.
Texture* getDialougeTexture(DialougeManager manager,DialougeRequest request,
                            SDL_Renderer* renderer, TTF_Font* gFont, int* nWritten);

#endif
