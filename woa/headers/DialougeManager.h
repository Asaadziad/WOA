#ifndef DIALOUGE_MANAGER_H
#define DIALOUGE_MANAGER_H

#include "Dialouge.h"
#include "texture.h"


typedef struct dialougem_t* DialougeManager;


DialougeManager initDialougeManager();
void destroyDialogeManager(DialougeManager manager);

// Dialouge actions.
Texture getDialougeTexture(DialougeManager manager,DialougeRequest request, int w, int h);

#endif
