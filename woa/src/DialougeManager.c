#include "stdlib.h"

#include "../headers/DialougeManager.h"
#include "../headers/DialougeStorage.h"
#include "../headers/Dialouge.h"

struct dialougem_t {   
    DialougeStorage dialouges;  // Dialouges storage
};


DialougeManager initDialougeManager(){
    DialougeManager m = (DialougeManager)malloc(sizeof(*m));
    if(!m) return NULL;
    m->dialouges = initDialougeStorage();
    return m;
}


// Prepares the dialouge texture for the texture manager
// to render it.
Texture getDialougeTexture(DialougeManager manager,DialougeRequest request){
    DialougeResponse res = getDialouge(manager->dialouges, request);
    Texture t = NULL; 
    // TODO:: Check if res has an error

    // TODO:: prepare a texture using the dialouge respons

    return t;
}
