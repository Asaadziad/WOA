#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "vec3.h"
#include "TextureManager.h"
#include "SDL2/SDL.h"
typedef enum {
  FIREBALL,
} ProjectileType;

typedef struct projectile_t* PROJECTILE;



/* @description: initiates a projectile on position (x,y) with the speed z
 * @args: pos_speed_vec - 3 points vector, type - projectile type
   @return: PROJECTILE - projectile object
   */
PROJECTILE createProjectile(Vec3 pos_speed_vec, ProjectileType type);

void destroyProjectile(PROJECTILE p);
void projectileRender(TextureManager manager,PROJECTILE p, SDL_Renderer* renderer, SDL_Rect camera); 
void projectileUpdate(PROJECTILE p, Vec3 new_pos_speed); 
int getProjectileLifeFrames(PROJECTILE p); 
Vec3 getProjectileVector(PROJECTILE p);

#endif
