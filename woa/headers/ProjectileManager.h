#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H

#include "hashtable.h"

typedef struct porjectile_manager_t* ProjectileManager;

ProjectileManager initProjectileManager();
void destroyProjectileManager(ProjectileManager p_manager);


#endif
