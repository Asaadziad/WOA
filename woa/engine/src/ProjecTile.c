#include "../../headers/ProjecTile.h"
#include "stdlib.h"

struct projectile_t {
  Vec3 v;
  ProjectileType type;
};

PROJECTILE createProjectile(Vec3 pos_speed_vec, ProjectileType type) {
  PROJECTILE new_projectile = (PROJECTILE)malloc(sizeof(*new_projectile));
  if(!new_projectile) return NULL;
  new_projectile->v = (Vec3)malloc(sizeof(Vec3));
  if(!new_projectile->v) return NULL;
  copyVec(new_projectile->v, pos_speed_vec); 
  new_projectile->type = type;
  return new_projectile;
}

Vec3 getProjectileVec(PROJECTILE p) {
  return p->v;
}

ProjectileType getProjectileType(PROJECTILE p) {
  return p->type;
}

void setProjectileVec(PROJECTILE p , Vec3 new_v){
  copyVec(p->v, new_v);
}

void destroyProjectile(PROJECTILE p) {
  free(p);
}
