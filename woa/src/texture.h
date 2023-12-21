#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "vector.h"


typedef struct texture_t* Texture;

int getTextureId(Texture t);
int getTextureLabelId(Texture t);
int getTextureHeight(Texture t);
int getTextureWidth(Texture t);
SDL_Texture* getTexturePtr(Texture t);



Texture initTexture(int render_x,int render_y,int id);
Texture loadTextureFromFile(SDL_Renderer* renderer,const char* path,int id);
Texture loadTextureFromText(SDL_Renderer* renderer,TTF_Font* font,const char* text,SDL_Color* color);


void freeTexture(Texture texture);



#endif
