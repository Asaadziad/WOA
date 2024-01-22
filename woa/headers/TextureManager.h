#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "texture.h"
#include "stdbool.h"
#include "DialougeManager.h"
typedef struct texturem_t* TextureManager;

TextureManager textureManagerInit();
void destroyTextureManager(TextureManager manager);


/* Loading functions */

/*
 * args   :  manager   - struct (TextureManager)
 *          renderer   - the game renderer (current: SDL_Renderer)
 *          file_name  - string
 * return : texture    - Texture       
 * */
void load(TextureManager manager,SDL_Renderer* renderer,char* file_name);
//TODO:: loading text shall take as args only text and color
void loadText(TextureManager manager,SDL_Renderer* renderer,TTF_Font* font, const char* text,SDL_Color* color);

/* Drawing functions  */
void draw(TextureManager manager,int id,int x,int y,int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip);
void drawFrame(TextureManager manager,char* name,int x,int y,int frame_width, int frame_height,int render_width,int render_height,int current_row,int current_frame, SDL_Renderer* renderer, SDL_RendererFlip flip);
void drawText(TextureManager manager,int label_id,int x,int y,
            int width, int height, SDL_Color color,SDL_Renderer* renderer);
void drawSprite(TextureManager manager, int id,int x,int y, int width,int height, int sprite_x,int sprite_y,SDL_Renderer* renderer);
void drawRect(int x,int y,int height,int width,SDL_Color color,bool isFill,float fill_width,SDL_Renderer* renderer);
void drawDialouge(TextureManager manager,
                  SDL_Renderer* renderer, 
                  int x, int y,
                  TTF_Font* gFont,
                  DialougeManager dManager,
                  DialougeRequest request); 

#endif
