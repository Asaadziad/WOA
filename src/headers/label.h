#ifndef LABEL_H
#define LABEL_H

#include "vector.h"
#include "game.h"
#include "SDL2/SDL.h"

typedef struct {
    SDL_Texture* labelTexture;
    Vector2f position;  
    int width;
    int height;  
} *Label;

Label createLabel(Game game,const char* text,int x, int y);

#endif