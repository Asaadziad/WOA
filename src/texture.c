#include "texture.h"
#include "string.h"
#include "logger.h"

Texture initTexture(int render_x,int render_y,TexType type){
    
    Texture new_texture = (Texture)malloc(sizeof(*new_texture));
    if(!new_texture) return NULL;
    new_texture->height = 0;
    new_texture->width = 0;
    new_texture->texture = NULL;
    Vector2f starter_pos = {render_x,render_y};
    new_texture->render_pos = starter_pos;
    new_texture->type = type;
    return new_texture;
}

Texture loadTextureFromFile(SDL_Renderer* renderer,const char* path,TexType type){
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
    Texture t = initTexture(0,0,type);
    t->texture = texture;
    t->height = surface->h;
    t->width = surface->w;
    
    SDL_FreeSurface( surface );

    return t;
}

void loadTextureFromText(SDL_Renderer* renderer,TTF_Font* font,Texture texture, const char* text){
    SDL_Texture* label;

    SDL_Color black = {0,0,0,0};
    SDL_Surface* surface = TTF_RenderText_Solid(font,text,black);
    if(!surface) return;

    label = SDL_CreateTextureFromSurface(renderer , surface );

    texture->texture = label;
    texture->height = surface->h;
    texture->width = surface->w;
    SDL_FreeSurface( surface );
}

void freeTexture(Texture texture){
    SDL_DestroyTexture(texture->texture);
    free(texture);
}
