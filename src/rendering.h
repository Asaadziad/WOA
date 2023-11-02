#ifndef RENDERING_H
#define RENDERING_H

#include "SDL2/SDL.h"
#include "game.h"
#include "tile.h"
#include "label.h"
#include "texture.h"
#include "object.h"

void renderPlayer(Game game,Player p);
void renderLabel(Game game);
void renderObject(Game game,OBJECT obj);

void renderTexture(Game game,Texture texture);
void renderTextureAt(Game game,Texture texture,int x, int y);
void renderPartOfTexture(Game game, Texture texture,SDL_Rect dst,int x, int y);
void renderButton(Game game,int x, int y,const char* text);

#endif