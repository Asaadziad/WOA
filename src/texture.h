#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "vector.h"

typedef struct texture_t{
    int height;
    int width;
    Vector2f render_pos;
    SDL_Texture* texture;
} *Texture;

Texture initTexture(int render_x,int render_y);
void loadTexture(SDL_Renderer* renderer,Texture texture, const char* path);
void loadTextureFromText(SDL_Renderer* renderer,TTF_Font* font,Texture texture, const char* text);

void setRenderX(Texture texture,int new_x);
void setRenderY(Texture texture,int new_y);



void freeTexture(Texture texture);



#endif