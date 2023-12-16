#include "stdlib.h"
#include "string.h"
#include "stdio.h"
typedef struct token {
  char* key;
  char* lValue;
  int nValue;
} *Token;

int find_index(char* string, char delim){
  int index = 0;
  while(*string != '\0'){
    if(*string == delim) {
      return index;
    }
    index += 1;
    string = string +1;
  }
  return -1;
}

Token tokenize(char* line){
  Token t = (Token)malloc(sizeof(*t));
  if(!t) return NULL;
  t->key = NULL;
  t->lValue = NULL;
  t->nValue = 0;
  return t;
}
int main(){
  char* line = "id: 1";
  int splitted_index = find_index(line, ':');
  char* s = (char*)malloc(sizeof(char)* splitted_index);
  char* s2 = (char*)malloc(sizeof(char)* (strlen(line) - splitted_index));
  strncpy(s,line,splitted_index);
  strcpy(s2, line + splitted_index + 1);
  
  Token test = tokenize(line);
  fprintf(stderr, "%s ",s);

  free(s);
  free(s2);
}
