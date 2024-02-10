#include "../../headers/ProjectileManager.h"
#include "stdlib.h"
#include "../../headers/hashtable.h"

struct porjectile_manager_t {
  HashTable projectile_table;  
};


ProjectileManager initProjectileManager() {
  ProjectileManager manager = (ProjectileManager)malloc(sizeof(ProjectileManager));
  if(!manager) return NULL;
  manager->projectile_table = createTable();
  return manager;
}

void destroyProjectileManager(ProjectileManager p_manager){}


