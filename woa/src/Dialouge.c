#include "Dialouge.h"
#include "stdlib.h"


struct dialouge_t {
  int   id; 
  char* dialouge; // array of strings to save the sentences    
};

DIALOUGE createDialouge(int id,char* dialouge){
    DIALOUGE d = (DIALOUGE)malloc(sizeof(*d));
    if(!d) return NULL;
    d->id = id;
    d->dialouge = dialouge;
    return d;
}

void destroyDialouge(DIALOUGE dialouge){
    free(dialouge->dialouge);
    free(dialouge);
}
