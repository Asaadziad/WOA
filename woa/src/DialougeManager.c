#include "stdlib.h"

#include "SDL2/SDL_ttf.h"

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
Texture getDialougeTexture(DialougeManager manager,DialougeRequest request, SDL_Renderer* renderer, TTF_Font* gFont ){
    DialougeResponse res = getDialouge(manager->dialouges, request);
    Texture t = initTexture(0,0,0); 
    // TODO:: Check if res has an error
    if(res.error != DIALOUGE_SUCCESS) {
      return NULL; 
    }
    // TODO:: prepare a texture using the dialouge response
        
    char** sentences = getSentences(res.dialouge);
    SDL_Texture* current = NULL;
    for(int i = 0; i < getSentencesCount(res.dialouge) ;i++){
     SDL_Surface* surf = TTF_RenderText_Solid( gFont,sentences[i], request.fontColor );  
    if(!surf) continue;
    setTextureHeight(t, surf->h);
    setTextureWidth(t, surf->w);
    SDL_Texture* texture_ptr = SDL_CreateTextureFromSurface(renderer, surf);
    if(!texture_ptr) continue;
    setTexturePtr(t, texture_ptr); 
    if(current) {
      current->next = texture_ptr;
    }
    }
    return t;
}
