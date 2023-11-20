#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "texture.h"
#include "stdbool.h"
typedef struct texturem_t* TextureManager;

TextureManager textureManagerInit();

void load(TextureManager manager,SDL_Renderer* renderer,const char* file_name,TexType texture_type);
void loadText(TextureManager manager,SDL_Renderer* renderer,TTF_Font* font, const char* text);
void draw(TextureManager manager,TexType texture_type,int x,int y,int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip);
void drawFrame(TextureManager manager,TexType texture_type,int x,int y,int frame_width, int frame_height,int render_width,int render_height,int current_row,int current_frame, SDL_Renderer* renderer, SDL_RendererFlip flip);
void drawText(TextureManager manager,int label_id,int x,int y,
            int width, int height, SDL_Color color,SDL_Renderer* renderer);
void drawSprite(TextureManager manager, TexType texture_type,int x,int y, int width,int height, int sprite_x,int sprite_y,SDL_Renderer* renderer);
void drawRect(int x,int y,int height,int width,SDL_Color color,bool isFill,float fill_width,SDL_Renderer* renderer);
#endif