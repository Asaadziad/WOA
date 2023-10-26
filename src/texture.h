#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL_image.h"

typedef struct texture_t{
    int height;
    int width;
    SDL_Texture* texture;
    struct texture_t* next;
} *Texture;

Texture initTexture();
void loadTexture(SDL_Renderer* renderer,Texture texture, const char* path);
void loadTextureFromText(SDL_Renderer* renderer, const char* text);
void freeTexture(Texture texture);



#endif