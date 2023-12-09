#include "stdio.h"
#include "stdlib.h"
#include "string.h"

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
        char* start = line;
        if(*line == ' ' || *line == '\t' || *line == '\r' || *line == '\n'){
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

static void createObjectFromLine(char* line){
    if(!line) return;
    Token* tokens = tokenize(line);
    if(!tokens) return;
    for(int i = 0;i < 5;i++){
        if(tokens[i]){
            fprintf(stderr, "%s\n",tokens[i]->literal);
        }
    }
}

void setupObjects(const char* file_path){
    FILE* objects_file = fopen(file_path,"r");
    if(!objects_file) return;
    char* line;
    size_t len = 0;
    size_t read;
    while ((read = getline(&line, &len, objects_file)) != -1) {
        createObjectFromLine(line);
    }
    fclose(objects_file);
}

int main(){
    setupObjects("test.txt");
    return 0;
}