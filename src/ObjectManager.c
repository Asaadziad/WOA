#include "ObjectManager.h"
#include "DS/list.h"
#include "stdlib.h"
#include "stdio.h"
#include "object.h"

struct objm_t{
    List objects;
};

ObjectManager initObjectManager(){
    ObjectManager manager = (ObjectManager)malloc(sizeof(*manager));
    if(!manager) return NULL;
    manager->objects = listCreate(NULL,NULL,NULL);
    return manager;
}

typedef enum {
    LITERAL_TOKEN,
    NUMERIC_TOKEN,
} TokenType;

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
    while(*line != '\n'){
        char* start = line;
        int len = 0;
        while(*line != ' ' || *line != '\t' || *line != '\r'){
            len++;
            line++;
        }
        char* ident = (char*)malloc(sizeof(char) * (len+1));
        if(!ident) return NULL;
        strncpy(ident,start,len);
        ident[len] = '\0';
        arr[i] = tokenCreate(ident);
        i++;        
    }
    return arr;
}

static OBJECT createObjectFromLine(char* line){
    if(!line) return NULL;
    Token* tokens = tokenize(line);
    if(!tokens) return NULL;
    OBJECT tmp;
    char* obj_type = tokens[0]->literal;
    if(strcmp(obj_type,"TREE_OBJECT") == 0){
        tmp = createObject(atoi(tokens[1]->literal),
                            atoi(tokens[2]->literal),
                            atoi(tokens[3]->literal),
                            atoi(tokens[4]->literal),
                            TREE_OBJECT);
    }

    return tmp;
}

void setupObjects(ObjectManager manager,const char* file_path){
    FILE* objects_file = fopen(file_path,"r");
    char* line;
    size_t len = 0;
    size_t read;
    while ((read = getline(&line, &len, objects_file)) != -1) {
        listInsert(manager->objects,createObjectFromLine(line));
    }
    fclose(objects_file);
}