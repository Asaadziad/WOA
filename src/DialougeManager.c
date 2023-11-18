#include "DialougeManager.h"
#include "DS/list.h"
#include "stdlib.h"
#include "TextureManager.h"

struct dialougem_t {
    List dialouges;        
};

DialougeManager initDialougeManager(){
    DialougeManager m = (DialougeManager)malloc(sizeof(*m));
    if(!m) return NULL;
    m->dialouges = listCreate(NULL,NULL,NULL);
    return m;
}

/*
* setting dialouges up manually until i need it automated
*/
void setupDialouges(DialougeManager manager,const char* file_path){
}


void sendDialouge(int dialouge_id){   
}