#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "headers/ObjectManager.h"
#include "headers/object.h"
#include "headers/CollisionDetection.h"
#include "headers/logger.h"
#include "headers/DialougeManager.h"

struct objm_t{
    List objects;
};

static void destroyObjPtr(void* elem){
    destroyObject((OBJECT)elem);
}

static void printObjectPtr(void* elem){
    printObject((OBJECT)elem);
}

static bool compareObjectPtr(void* elem1,void* elem2){
    return checkObjectsTypes((OBJECT)elem1,(OBJECT)elem2);
}

ObjectManager initObjectManager(){
  //ObjectManager manager = (ObjectManager)malloc(sizeof(*manager));
  // if(!manager) return NULL;
    //manager->objects = listCreate(destroyObjPtr,compareObjectPtr,printObjectPtr);
    //return manager;
  return NULL;
}

typedef struct token_t* Token;
struct token_t {
    char* literal;
};

static Token tokenCreate(char* literal){
    Token t = (Token)malloc(sizeof(*t));
    if(!t) return NULL;
    t->literal = literal;
    return t;
}


//TODO :: debug
Token* tokenize(char* line){
    if(!line) return NULL;
    Token* arr = (Token*)malloc(sizeof(*arr) * 5); // hardcoded for test purposes
    if(!arr) return NULL;
    int i = 0;
    char* first_letter = line;
    int len = 0;
    while(*line != '\0'){
        if(*line == ' ' || *line == '\t' || *line == '\r' || *line == '\n' || *line == '\0'){
            line++;
            char* ident = (char*)malloc(sizeof(*ident) * (len+1));
            if(!ident) return NULL;
            strncpy(ident,first_letter,len);
            ident[len] = '\0';
            arr[i] = tokenCreate(ident);
            i++;
            len = 0;
            first_letter = line;
            continue;
        }
        len++;
        line++;        
    }
    return arr;
}

static OBJECT createObjectFromLine(char* line){
    if(!line) return NULL;
    Token* tokens = tokenize(line);
    if(!tokens) return NULL;
    OBJECT tmp = NULL;
    char* obj_type = tokens[0]->literal;
    if(strcmp(obj_type,"TREE_OBJECT") == 0){
        tmp = createObject(TILE_WIDTH,
                            TILE_HEIGHT,
                            atoi(tokens[3]->literal)*TILE_WIDTH,
                            atoi(tokens[4]->literal)*TILE_WIDTH,
                            TREE_OBJECT);
        
    } else if(strcmp(obj_type,"SWORD_OBJECT") == 0){
        tmp = createObject(TILE_WIDTH,
                            TILE_HEIGHT,
                            atoi(tokens[3]->literal) * TILE_WIDTH,
                            atoi(tokens[4]->literal) * TILE_WIDTH,
                            SWORD_OBJECT);
        setObjectFrame(tmp,0);
    }
    for(int i = 0; i < 5;i++){
        if(tokens[i]){

        free(tokens[i]->literal);
        }
    }
    free(tokens);

    return tmp;
}

void setupObjects(ObjectManager manager,const char* file_path){
  /*FILE* objects_file = fopen(file_path,"r");
    char* line;
    size_t len = 0;
    size_t read;
    while ((read = getline(&line, &len, objects_file)) != -1) {
        OBJECT tmp  = createObjectFromLine(line);
        if(tmp){ 
            
            listInsert(manager->objects,tmp);
        }
    }

    fclose(objects_file);
  */
}

void renderObjects(ObjectManager manager,TextureManager texture_manager, SDL_Renderer* renderer,SDL_Rect camera){
    Node current = getHead(manager->objects);
    if(!current) {
        exit(1);
    }
    for(int i = 0; i < getListSize(manager->objects);i++){
        OBJECT tmp = getNodeData(current);
        if(isObjectRenderable(tmp)){
            objectDraw(texture_manager,tmp,renderer,camera);
        }
        current = getNextNode(current);
    }
}

Node getObjectsList(ObjectManager manager){
    Node tmp = getHead(manager->objects);
    return tmp;
}

void checkPlayerCollisionWithObjects(ObjectManager manager,Player p){
    Node current = getHead(manager->objects);
    for(int i = 0;i < getListSize(manager->objects);i++){
        OBJECT tmp  = getNodeData(current);
        if(!isObjectRenderable(tmp)){
            current = getNextNode(current);
            continue;
        }
        if(checkCollision(p,objectGetRect(tmp),true)){
            switch(objectGetType(tmp)){
                case SWORD_OBJECT:
                    p->isInDialouge = true;
                    break;
                default: break;
            }
        }
        current = getNextNode(current);
    }
}


OBJECT findObject(ObjectManager manager,ObjectType type){
    OBJECT tmp = CREATE_DEFAULT_OBJ(SWORD_OBJECT);
    OBJECT to_find = listFind(manager->objects,tmp);
    return to_find;
}

void deleteObject(ObjectManager manager, ObjectType type){
    // to be added
}


void destroyObjectManager(ObjectManager manager){
    if(!manager) return;
    if(manager->objects){
    listDestroy(manager->objects);
    }
    free(manager);
}
