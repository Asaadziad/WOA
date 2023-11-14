#ifndef COMPONENTS_MANAGER_H
#define COMPONENTS_MANAGER_H

#include "components.h"

typedef struct cmanager_t* ComponenetsManager;

ComponenetsManager initComponentsManager();

void addComponent(ComponenetsManager manager,COMPONENT c);
/*
* serach the DS that holds the components
* TODO :: implements a new version that requires id instead of enum type
* @return : return the search result (COMPONENET) && NULL if doesnt exist.
*/
COMPONENT findComponent(ComponenetsManager manager, ComponentType type);



#endif