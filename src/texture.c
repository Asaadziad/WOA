#include "texture.h"

Texture initTexture(){
    
    Texture new_texture = (Texture)malloc(sizeof(*new_texture));
    if(!new_texture) return NULL;
    new_texture->height = 0;
    new_texture->width = 0;
    new_texture->texture = NULL;
    new_texture->next = NULL;
    return new_texture;
}

void loadTexture(SDL_Renderer* renderer,Texture texture, const char* path){
    if(!texture) return;
    SDL_DestroyTexture(texture->texture);
    SDL_Surface* surface = IMG_Load(path);
    if(!surface){
        fprintf(stderr,"Could'nt Load surface : %s", SDL_GetError());
        exit(1);
    }

    //Color key image
	SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0, 0xFF, 0xFF ) );

    SDL_Texture* new_t = SDL_CreateTextureFromSurface(renderer,surface);
    if(!new_t) {
        fprintf(stderr,"Could'nt Load texture : %s", SDL_GetError());
        exit(1);
    }

    texture->height = surface->h;
    texture->width = surface->w;
    texture->texture = new_t;

    SDL_FreeSurface(surface);
}


void freeTexture(Texture texture){
    SDL_DestroyTexture(texture->texture);
    free(texture);
}
