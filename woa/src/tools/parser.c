#include "parser.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


typedef struct token {
  char* key;
  char* lValue;
  int nValue;
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
  char* token = strtok(line, ":");
  t->key = NULL;
  t->lValue = NULL;
  t->nValue = 0;
  return t;
}


char* strip_from_white_spaces(char* string) {
  char* s_string = NULL;
  char* start_ptr = string;
  char *current = string;
  size_t len = 0;
  while(*current != '\0') {
    if(*current == ' '){
      current = current+1;
      continue;
    }
    len++;
    current = current +1;
  }

  s_string = (char*)malloc(sizeof(char) * (len + 1));
  if(!s_string) return NULL;
  int index = 0;
  s_string[len] = '\0';
  while(index < len) {
    if(*start_ptr == ' '){
      start_ptr = start_ptr +1;
      continue;
    }
    s_string[index] = *start_ptr;
    index++;
    start_ptr = start_ptr + 1;
  }
  return s_string;
}


JSONObject* parse(const char* file_path){
  FILE* file = fopen(file_path, "r");
  
  char* buffer = NULL;
  size_t len = 0;
 
  JSONObject* objects = NULL;

  while(getline(&buffer, &len,file ) != -1){
    //TODO:: if we read an object opener ( { ) : create json  
 /*   JSONObject obj = createJsonObj();
    if(!obj) continue;
    while(!strcmp(buffer, "}")){
       obj->tokens[obj->size] = tokenize(buffer);    
       obj->size++;
       //TODO:: read next line
    }
*/
    printf("%s",strip_from_white_spaces(buffer));
    //TODO:: add obj to an array of JSon objects
    }

  fclose(file);
  if(buffer) free(buffer);
  return objects;
}
 int main(){
  parse("../data/dialouges.json");
 return 0;
 }
