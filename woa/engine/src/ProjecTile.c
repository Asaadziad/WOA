#include "../../headers/ProjecTile.h"
#include "stdlib.h"
#include "SDL2/SDL.h"
#include "../../headers/TextureManager.h"

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

void projectileUpdate(PROJECTILE p, Vec3 new_pos_speed) {
  copyVec(p->v, new_pos_speed);
}

void projectileRender(TextureManager manager,PROJECTILE p, SDL_Renderer* renderer, SDL_Rect camera) {
  switch(p->type) {
    case FIREBALL:
        drawFrame(manager,"fire.png",getX(p->v),getY(p->v),48,
            48,48,48,1,0,
            renderer, SDL_FLIP_NONE); 
      break;
    default: break; 
  }
}



void destroyProjectile(PROJECTILE p) {
  free(p);
}
