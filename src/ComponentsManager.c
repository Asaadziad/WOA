#include "ComponentsManager.h"
#include "DS/list.h"
#include "common.h"

struct cmanager_t {
    List components;
};

static void freeComponentPtr(void* elem){
    destroyComponent((COMPONENT)elem);
}

static bool compareComponentPtr(void* elem1,void* elem2){
    bool t = componentsCompare((COMPONENT)elem1,(COMPONENT)(elem2));
    return t;
}

ComponenetsManager initComponentsManager(){
    ComponenetsManager m = (ComponenetsManager)malloc(sizeof(*m));
    if(!m) return NULL;
    m->components = listCreate(freeComponentPtr,compareComponentPtr,NULL);
    if(!m->components) return NULL;
    return m;
}

void addComponent(ComponenetsManager manager,COMPONENT c){
    listInsert(manager->components,c);
}

COMPONENT findComponent(ComponenetsManager manager, ComponentType type){
    COMPONENT tmp = createComponent(0,0,0,0,type,0,0);
    if(!tmp) return NULL;
    COMPONENT found = ((COMPONENT)listFind(manager->components,(void*)tmp));
    destroyComponent(tmp);
    return found;
}