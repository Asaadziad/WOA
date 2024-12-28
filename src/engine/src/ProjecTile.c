#include "stdlib.h"
#include "SDL2/SDL.h"

#include "headers/ProjecTile.h"
#include "headers/TextureManager.h"

struct projectile_t {
  Vec3 v;
  ProjectileType type;
  int life_frames;
  SDL_Rect collision_box;
};

PROJECTILE createProjectile(Vec3 pos_speed_vec, ProjectileType type) {
  PROJECTILE new_projectile = (PROJECTILE)malloc(sizeof(*new_projectile));
  if(!new_projectile) return NULL;
  new_projectile->v = (Vec3)malloc(sizeof(Vec3));
  if(!new_projectile->v) return NULL;
  copyVec(new_projectile->v, pos_speed_vec); 
  new_projectile->type = type;
  new_projectile->life_frames = 0;
  SDL_Rect src;
  src.x = getX(pos_speed_vec) + 8;
  src.y = getY(pos_speed_vec) + 8;
  src.h = 32;
  src.w = 32;
  new_projectile->collision_box = src;
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

int getProjectileLifeFrames(PROJECTILE p) {
  return p->life_frames;
}

void projectileUpdate(PROJECTILE p, Vec3 new_pos_speed) {
  p->life_frames++;
  copyVec(p->v, new_pos_speed);
  p->collision_box.x = getX(p->v) + 8;
  p->collision_box.y = getY(p->v) + 8;
}

void projectileRender(TextureManager manager,PROJECTILE p, SDL_Renderer* renderer, SDL_Rect camera) {
  switch(p->type) {
    case FIREBALL:
      drawRect(p->collision_box.x - camera.x, p->collision_box.y - camera.y, p->collision_box.h, p->collision_box.w, (SDL_Color){0,0,0,0}, false,0, renderer);  
      drawFrame(manager,"fire.png",getX(p->v) - camera.x,getY(p->v) - camera.y,48,
            48,48,48,1,0,
            renderer, SDL_FLIP_NONE); 
      break;
    default: break; 
  }
}

Vec3 getProjectileVector(PROJECTILE p) {
  return p->v;
}

void destroyProjectile(PROJECTILE p) {
  free(p->v);
  free(p);
}
