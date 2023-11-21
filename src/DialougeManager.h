#ifndef DIALOUGE_MANAGER_H
#define DIALOUGE_MANAGER_H

#include "TextureManager.h"

typedef struct dialougem_t* DialougeManager;


DialougeManager initDialougeManager();
void setupDialouges(DialougeManager manager,const char* file_path);
void renderDialouge(TextureManager manager,int* dialouge_ids);
void sendDialouge(int dialouge_id);


#endif