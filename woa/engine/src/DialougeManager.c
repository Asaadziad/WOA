#include "stdlib.h"

#include "SDL2/SDL_ttf.h"

#include "../../headers/DialougeManager.h"
#include "../../headers/DialougeStorage.h"
#include "../../headers/Dialouge.h"

struct dialougem_t {   
    DialougeStorage dialouges;  // Dialouges storage
};


DialougeManager initDialougeManager(){
    DialougeManager m = (DialougeManager)malloc(sizeof(*m));
    if(!m) return NULL;
    m->dialouges = initDialougeStorage();
    return m;
}

static
Texture createTextureFromText(char* sentence, 
                            SDL_Renderer* renderer,
                            TTF_Font* gFont,
                            SDL_Color fontColor) {
      Texture t = initTexture(0, 0, 0);
      SDL_Surface* surf = TTF_RenderText_Solid( gFont, sentence, fontColor );  
      if(!surf) {
        free(t);
        fprintf(stderr, "Failed to create surface");
        return NULL;
      };
      setTextureHeight(t, surf->h);
      setTextureWidth(t, surf->w);
      SDL_Texture* texture_ptr = SDL_CreateTextureFromSurface(renderer, surf);
      if(!texture_ptr) {
        free(t);
        free(surf);
        fprintf(stderr, "Failed to create texture");
        return NULL;
      };
      setTexturePtr(t, texture_ptr);
      free(surf);
    return t;
}

// Prepares the dialouge texture for the texture manager
// to render it.
Texture* getDialougeTexture(DialougeManager manager,DialougeRequest request, SDL_Renderer* renderer, TTF_Font* gFont, int* nWritten ){
    DialougeResponse res = getDialouge(manager->dialouges, request); 
    // TODO:: Check if res has an error
    if(res.error != DIALOUGE_SUCCESS) {
      return NULL; 
    }
    // TODO:: prepare a texture using the dialouge response
    int sentences_n = getSentencesCount(res.dialouge);
    *nWritten = sentences_n;
    Texture* texturesArray = (Texture*)malloc(sizeof(Texture) * sentences_n);
    if(!texturesArray) {
      fprintf(stderr, "Failed to allocate texture array");
      return NULL;
    }
    char** sentences = getSentences(res.dialouge);
    if(!sentences) {
      free(texturesArray);
      return NULL;
    } 
    // for each sentence we create a texture
    for(int i = 0; i < sentences_n ;i++){
      texturesArray[i] = createTextureFromText(sentences[i], renderer, gFont, request.fontColor);
    }

    return texturesArray;
}
