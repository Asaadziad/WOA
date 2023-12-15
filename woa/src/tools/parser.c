#include "parser.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


typedef struct token {

} *Token;

struct json_obj {
    int    size; // num of tokens
    Token* tokens;
};


/*
 *  Creates an empty Json object
 * */
JSONObject createJsonObj(){
  JSONObject j = (JSONObject)malloc(sizeof(*j));
  if(!j) {
    fprintf(stderr, "Couldn't create json object");
    return NULL;
  }
  j->size = 0;
  j->tokens = NULL;
  return j;
}

Token tokenize(char* line){
  Token t = (Token)malloc(sizeof(*t));
  if(!t) return NULL;


  return t;
}


JSONObject* parse(const char* file_path){
  FILE* file = fopen(file_path, "r");
  
  char* buffer = NULL;
  size_t len = 0;
 
  JSONObject* objects = NULL;

  while(getline(&buffer, &len,file ) != -1){
    // if we read an object opener ( { ) : create json  
    JSONObject obj = createJsonObj();
    if(!obj) continue;
    while(!strcmp(buffer, "}")){
       obj->tokens[obj->size] = tokenize(buffer);    
       obj->size++;
       //TODO:: read next line
    }

    //TODO:: add obj to an array of JSon objects
    }

  fclose(file);
  if(buffer) free(buffer);
  return objects;
}

