#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL_image.h"

typedef struct {
    int height;
    int width;
    SDL_Texture* texture;
} Texture;

Texture* initTexture();
void loadTexture(SDL_Renderer* renderer,Texture* texture, const char* path);
void freeTexture(Texture* texture);

#endif