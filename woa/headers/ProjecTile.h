#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "vec3.h"

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

#endif
