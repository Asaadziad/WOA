#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL_image.h"

typedef struct texture_t* Texture;

// setters
void setTextureId(Texture t, int id);
void setTextureLabelId(Texture t, int label_id);
void setTexturePtr(Texture t, SDL_Texture* t_ptr);
void setTextureHeight(Texture t, int height);
void setTextureWidth(Texture t, int width);

// getters
int getTextureId(Texture t);
int getTextureLabelId(Texture t);
int getTextureHeight(Texture t);
int getTextureWidth(Texture t);
SDL_Texture* getTexturePtr(Texture t);

Texture initTexture(int render_x,int render_y,int id);
void freeTexture(Texture texture);

#endif
