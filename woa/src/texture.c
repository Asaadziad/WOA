#include "../headers/texture.h"
#include "string.h"
#include "../headers/vector.h"

#include "SDL2/SDL_ttf.h"


struct texture_t {
    int height;
    int width;
    int id;

    Vector2f render_pos;
    SDL_Texture* texture;    
    SDL_Texture* next; // in case i want to save a chain of textures to be rendered simultaneously   
};

void setTexturePtr(Texture t, SDL_Texture* t_ptr) {
  t->texture = t_ptr;
}

void setTextureId(Texture t, int id){
  t->id = id;
}



void setTextureHeight(Texture t, int height){
  t->height = height;
}

void setTextureWidth(Texture t, int width) {
  t->width = width;
}

int getTextureId(Texture t){
  return t->id;
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

    return new_texture;
}

void freeTexture(Texture texture){
    SDL_DestroyTexture(texture->texture);
    free(texture);
}
