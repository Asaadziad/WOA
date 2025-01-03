#include "limits.h"
#include "stdio.h"

#include "headers/TextureManager.h"
#include "headers/list.h"
#include "headers/texture.h"
#include "headers/common.h"
#include "headers/logger.h"
#include "headers/hashtable.h"
#include "headers/DialougeManager.h"
#include "headers/Dialouge.h"

#define PATH_MAX 1024

struct texturem_t {
    HashTable texturesTable;
};



TextureManager textureManagerInit(){
    TextureManager manager = (TextureManager)malloc(sizeof(*manager));
    if(!manager) return NULL;
    manager->texturesTable = createTable();
    if(!manager->texturesTable) {return NULL;}
    return manager;
}

internal
Texture loadTextureFromFile(SDL_Renderer* renderer, const char* path){
    SDL_Texture* texture;

    SDL_Surface* surface = IMG_Load(path);
    
    if(!surface) {
        ERR("Couldn't load file");
        return NULL;
    }

    texture = SDL_CreateTextureFromSurface( renderer, surface );
    if(!texture) {
        ERR("Couldn't create texture");
        return NULL;
    }
    Texture t = initTexture(0,0,0);
    if(!t) return NULL;
    setTexturePtr(t, texture);
    setTextureHeight(t, surface->h);
    setTextureWidth(t, surface->w);
    
    SDL_FreeSurface( surface );

    return t;
}

// TODO :: load shall return the id of the texture.
void load(TextureManager manager,SDL_Renderer* renderer, char* file_name){
  char path[PATH_MAX] = "";
    char* resourcesPath = "./res/";
    strcat(path, resourcesPath);
    strcat(path, file_name); 
    Texture new_t = loadTextureFromFile(renderer, path);
    if(!new_t) {
      ERR("Couldn't load texture");
      return;
    }

    //TODO:: convert from list to array
    //listInsert(manager->textures,new_t);
    tableInsert(manager->texturesTable, file_name, new_t);
}

void loadText(TextureManager manager,SDL_Renderer* renderer,TTF_Font* font, const char* text,SDL_Color* color){}

void draw(TextureManager manager,int id,int x,int y,
            int width, int height, SDL_Renderer* renderer,
            SDL_RendererFlip flip){

    Texture to_render = NULL;
    if(!to_render) return;
    
    SDL_Rect src;
    SDL_Rect dst;
    src.x = 0;
    src.y = 0;
    src.h = dst.h = height;
    src.w = dst.w = width;
    dst.x = x;
    dst.y = y;

    SDL_RenderCopyEx(renderer,getTexturePtr(to_render),&src,&dst,0,0,flip);
}

void drawFrame(TextureManager manager, char* name,int x,int y,int frame_width,
            int frame_height,int render_width,int render_height,int current_row,int current_frame,
            SDL_Renderer* renderer, SDL_RendererFlip flip){

    Texture to_render = (Texture)tableSearch(manager->texturesTable, name);
    if(!to_render) return;
    
    SDL_Rect src;
    SDL_Rect dst;
    src.x = frame_width * current_frame;
    src.y = frame_height * (current_row - 1);
    src.h = frame_height;
    src.w = frame_width;
    dst.w = render_width;
    dst.h = render_height;
    dst.x = x;
    dst.y = y;

    SDL_RenderCopyEx(renderer,
       getTexturePtr(to_render),
       &src, &dst,
       0,0, 
       flip);
}

void drawText(TextureManager manager,int label_id,int x,int y,
            int width, int height, SDL_Color color,SDL_Renderer* renderer){
        
        
                
}

void drawSprite(TextureManager manager, int id,int x,int y, int width,int height, int sprite_x,int sprite_y,SDL_Renderer* renderer){
    Texture to_render = NULL;
    if(!to_render) return;
    
    SDL_Rect src;
    SDL_Rect dst;
    src.x = sprite_x;
    src.y = sprite_y;
    src.h = dst.h = height;
    src.w = dst.w = width;
    dst.x = x;
    dst.y = y;

    SDL_RenderCopy(renderer, 
                  getTexturePtr(to_render), 
                  &src, 
                  &dst);
}

void drawRect(int x,int y,int height,int width,SDL_Color color,bool isFill,float fill_width,SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);
    SDL_Rect rect;
    rect.x =x;
    rect.y = y;
    rect.h = height;
    rect.w = width;
    if(isFill){
        SDL_RenderDrawRect(renderer,&rect);
        rect.w = fill_width - 2;
        rect.h -=2;
        rect.x +=1;
        rect.y += 1;
        SDL_RenderFillRect(renderer,&rect);
    } else {
        SDL_RenderDrawRect(renderer,&rect);

    }
}

void drawDialouge(TextureManager manager,
                  SDL_Renderer* renderer, 
                  int x, int y,
                  TTF_Font* gFont,
                  DialougeManager dManager,
                  DialougeRequest request) {
  int sentencesWritten = 0;
  Texture* to_render = getDialougeTexture(dManager, request, renderer, gFont, &sentencesWritten);
  if(!to_render) {
    fprintf(stderr, "Couldn't initiate texture");
    return;
  }

    SDL_Rect src;
    SDL_Rect dst;
    src.x = 0;
    src.y = 0;
      // Here you loop on the array . :)
    int old_height = 0;
   for(int i =0; i < sentencesWritten; i++) {
    if(!to_render[i]) continue;
    src.h = dst.h = getTextureHeight(to_render[i]);
    src.w = dst.w = getTextureWidth(to_render[i]);
    dst.x = x;
    dst.y = y + old_height;
    SDL_Texture* texture = getTexturePtr(to_render[i]);
    if(!texture) continue;
    SDL_RenderCopy(renderer,texture, &src, &dst);
    old_height += dst.h;
   }  
}

void destroyTextureManager(TextureManager manager){
    if(!manager) return;
    free(manager);
}
