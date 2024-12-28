#include "stdlib.h"

#include "headers/ProjectileManager.h"
#include "headers/ProjecTile.h"

#define PROJECTILE_ARR_STARTER 8


struct porjectile_manager_t {
   PROJECTILE* projectiles;
   int len;
   int size;
};


ProjectileManager initProjectileManager() {
  ProjectileManager manager = (ProjectileManager)malloc(sizeof(ProjectileManager));
  if(!manager) return NULL;
  manager->projectiles = (PROJECTILE*)malloc(sizeof(PROJECTILE) * PROJECTILE_ARR_STARTER);
  if(!manager->projectiles) return NULL;
  manager->len = 0;
  manager->size = PROJECTILE_ARR_STARTER;
  return manager;
}

void insertProjectile(ProjectileManager manager,int x, int y, int speed, ProjectileType type) {
  int i_to_insert = 0;
  int is_full = 0;
  for(int j = 0 ; j < manager->size; j++ ) {
    if(!manager->projectiles[j]) {i_to_insert = j; break;};
    is_full++;
  }
  if (is_full >= 7) return;
   manager->projectiles[i_to_insert] = createProjectile(initVec3(x,y,speed),type);
}

void projectilesRender(ProjectileManager manager, TextureManager texture_manager, SDL_Renderer* renderer, SDL_Rect camera) {
  for(int i = 0; i < manager->size; i++) {
    if(!manager->projectiles[i]) continue;
    projectileRender(texture_manager, manager->projectiles[i], renderer, camera);
  }

}

void projectilesUpdate(ProjectileManager manager) {
  for(int i = 0; i < manager->size; i++) {
    if(!manager->projectiles[i]) continue;
    Vec3 new_v = getProjectileVector(manager->projectiles[i]);
    setX(new_v, getX(new_v) + getZ(new_v)); 
    projectileUpdate(manager->projectiles[i], new_v);
    if(getProjectileLifeFrames(manager->projectiles[i]) > 119) {
    destroyProjectile(manager->projectiles[i]);
    manager->projectiles[i] = NULL;
    
  }

  }
  
}

void destroyProjectileManager(ProjectileManager p_manager){
  // TODO::// loop on the array and destroy each projctile
  free(p_manager->projectiles);
}


