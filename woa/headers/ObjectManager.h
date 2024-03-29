#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "TextureManager.h"
#include "DialougeManager.h"
#include "SDL2/SDL.h"
#include "list.h"
#include "player.h"

typedef struct objm_t* ObjectManager;

ObjectManager initObjectManager();

void setupObjects(ObjectManager manager,const char* file_path);
void renderObjects(ObjectManager manager,TextureManager texture_manager,SDL_Renderer* renderer,SDL_Rect camera);

void checkPlayerCollisionWithObjects(ObjectManager manager,Player p);

OBJECT findObject(ObjectManager manager,ObjectType type);
void deleteObject(ObjectManager manager, ObjectType type);
Node getObjectsList(ObjectManager manager);
void destroyObjectManager(ObjectManager manager);
#endif