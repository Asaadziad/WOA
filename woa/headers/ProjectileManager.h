#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H

#include "hashtable.h"
#include "TextureManager.h"
#include "SDL2/SDL.h"
#include "ProjecTile.h"

typedef struct porjectile_manager_t* ProjectileManager;

ProjectileManager initProjectileManager();
void destroyProjectileManager(ProjectileManager p_manager);
void insertProjectile(ProjectileManager manager,int x, int y, int speed, ProjectileType type); 
void projectilesRender(ProjectileManager manager, TextureManager texture_manager, SDL_Renderer* renderer, SDL_Rect camera); 
void projectilesUpdate(ProjectileManager manager);

#endif
