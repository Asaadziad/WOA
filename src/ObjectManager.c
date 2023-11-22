#include "ObjectManager.h"
#include "stdlib.h"
#include "stdio.h"
#include "object.h"
#include "CollisionDetection.h"
#include "logger.h"
#include "DialougeManager.h"

struct objm_t{
    List objects;
};

static void destroyObjPtr(void* elem){
    destroyObject((OBJECT)elem);
}

static void printObjectPtr(void* elem){
    printObject((OBJECT)elem);
}

ObjectManager initObjectManager(){
    ObjectManager manager = (ObjectManager)malloc(sizeof(*manager));
    if(!manager) return NULL;
    manager->objects = listCreate(destroyObjPtr,NULL,printObjectPtr);
    return manager;
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
        tmp = createObject(atoi(tokens[1]->literal),
                            atoi(tokens[2]->literal),
                            atoi(tokens[3]->literal),
                            atoi(tokens[4]->literal),
                            TREE_OBJECT);
        
    } else if(strcmp(obj_type,"SWORD_OBJECT") == 0){
        tmp = createObject(atoi(tokens[1]->literal),
                            atoi(tokens[2]->literal),
                            atoi(tokens[3]->literal),
                            atoi(tokens[4]->literal),
                            SWORD_OBJECT);
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
    FILE* objects_file = fopen(file_path,"r");
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
}

void renderObjects(ObjectManager manager,TextureManager texture_manager, SDL_Renderer* renderer,SDL_Rect camera){
    Node current = getHead(manager->objects);
    if(!current) {
        exit(1);
    }
    for(int i = 0; i < getListSize(manager->objects);i++){
        OBJECT tmp = getNodeData(current);
        objectDraw(texture_manager,tmp,renderer,camera);
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
        if(checkCollision(p,objectGetRect(tmp))){
            switch(objectGetType(tmp)){
                case TREE_OBJECT:
                    
                break;
                case SWORD_OBJECT:
                    p->isInDialouge = true;
                    p->current_dialouge = SWORD_DIALOUGE;
                break;
                default: break;
            }
        }
        current = getNextNode(current);
    }
}

void destroyObjectManager(ObjectManager manager){
    if(!manager) return;
    if(manager->objects){
    listDestroy(manager->objects);
    }
    free(manager);
}