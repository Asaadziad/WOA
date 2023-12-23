#include "texture.h"
#include "string.h"
#include "vector.h"

#include "SDL2/SDL_ttf.h"


struct texture_t {
    int height;
    int width;
    Vector2f render_pos;
    SDL_Texture* texture;
    int id;    
    int label_id;
};

void setTexturePtr(Texture t, SDL_Texture* t_ptr) {
  t->texture = t_ptr;
}

void setTextureId(Texture t, int id){
  t->id = id;
}

void setTextureLabelId(Texture t, int label_id){
  t->label_id = label_id;
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

void freeTexture(Texture texture){
    SDL_DestroyTexture(texture->texture);
    free(texture);
}
