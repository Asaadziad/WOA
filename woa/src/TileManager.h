#ifndef TILE_MANAGER_H
#define TILE_MANAGER_H

#include "TextureManager.h"
#include "SDL2/SDL.h"

typedef struct tilemanager_t* TileManger;

TileManger initTileManager();
void destroyTileManager(TileManger manager);

void setupTiles(TileManger manager,const char* file_path);
void renderTiles(TileManger manager,TextureManager texture_manager,SDL_Renderer* renderer,SDL_Rect camera);

#endif