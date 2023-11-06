#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "SDL2/SDL.h"
#include "texture.h"

typedef struct texturem_t* TextureManager;

TextureManager textureManagerInit();

void load(TextureManager manager,SDL_Renderer* renderer,const char* file_name,TexType texture_type);
void draw(TextureManager manager,TexType texture_type,int x,int y,int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip);
void drawFrame(TextureManager manager,TexType texture_type,int x,int y,int width, int height,int current_row,int current_frame, SDL_Renderer* renderer, SDL_RendererFlip flip);

#endif