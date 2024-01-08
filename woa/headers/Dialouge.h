#ifndef DIALOUGE_H
#define DIALOUGE_H


typedef struct dialouge_t* DIALOUGE;


DIALOUGE createDialouge(int id, char* dialouge);
void destroyDialouge(DIALOUGE dialouge);

#endif
