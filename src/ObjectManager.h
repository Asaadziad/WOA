#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

typedef struct objm_t* ObjectManager;

ObjectManager initObjectManager();

void setupObjects(ObjectManager manager,const char* file_path);


#endif