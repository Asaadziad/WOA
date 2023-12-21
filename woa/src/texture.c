#include "texture.h"
#include "string.h"
#include "logger.h"

struct texture_t {
    int height;
    int width;
    Vector2f render_pos;
    SDL_Texture* texture;
    int id;    
    int label_id;
};

int getTextureId(Texture t){
  return t->id;
}

int getTextureLabelId(Texture t){
  return t->label_id;
}

int getTextureHeight(Texture t){
  return t->height;
}

int getTextureWidth(Texture t){
  return t->width;
}

SDL_Texture* getTexturePtr(Texture t){
  return t->texture;
}



Texture initTexture(int render_x,int render_y,int texture_id){
    
    Texture new_texture = (Texture)malloc(sizeof(*new_texture));
    if(!new_texture) return NULL;
    new_texture->height = 0;
    new_texture->width = 0;
    new_texture->texture = NULL;
    Vector2f starter_pos = {render_x,render_y};
    new_texture->render_pos = starter_pos;
    new_texture->id = texture_id;
    new_texture->label_id = -1;
    return new_texture;
}

Texture loadTextureFromFile(SDL_Renderer* renderer,const char* path,int id){
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
    Texture t = initTexture(0,0,id);
    if(!t) return NULL;
    t->texture = texture;
    t->height = surface->h;
    t->width = surface->w;
    
    SDL_FreeSurface( surface );

    return t;
}

Texture loadTextureFromText(SDL_Renderer* renderer,TTF_Font* font,const char* text,SDL_Color* color){
    SDL_Texture* label;

    SDL_Color black = {0,0,0,0};
    SDL_Surface* surface;
    if(color){
        surface = TTF_RenderText_Solid(font,text,*color);
    } else {
        surface = TTF_RenderText_Solid(font,text,black);
    }
    if(!surface) return NULL;

    label = SDL_CreateTextureFromSurface(renderer , surface );

    Texture texture = initTexture(0,0,1);
    if(!texture) {
        SDL_FreeSurface( surface );
        return NULL;
    }
    texture->texture = label;
    texture->height = surface->h;
    texture->width = surface->w;
    SDL_FreeSurface( surface );

    return texture;
}

void freeTexture(Texture texture){
    SDL_DestroyTexture(texture->texture);
    free(texture);
}
