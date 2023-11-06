#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "vector.h"
typedef enum {
    PLAYER_TEXTURE,
    LABEL_TEXTURE,
    TILE_TEXTURE,
} TexType;

typedef struct texture_t{
    int height;
    int width;
    Vector2f render_pos;
    SDL_Texture* texture;
    TexType type;
} *Texture;

Texture initTexture(int render_x,int render_y,TexType type);
Texture loadTextureFromFile(SDL_Renderer* renderer,const char* path,TexType type);

void loadTextureFromText(SDL_Renderer* renderer,TTF_Font* font,Texture texture, const char* text);


void freeTexture(Texture texture);



#endif