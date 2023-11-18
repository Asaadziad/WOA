#ifndef DIALOUGE_MANAGER_H
#define DIALOUGE_MANAGER_H

typedef struct dialougem_t* DialougeManager;


DialougeManager initDialougeManager();
void setupDialouges(DialougeManager manager,const char* file_path);
void sendDialouge(int dialouge_id);


#endif