#include "headers/Dialouge.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct dialouge_t {
  int   top; 
  char** sentences;    
};

int getSentencesCount(DIALOUGE d) {
  return d->top;
}

char** getSentences(DIALOUGE d) {
  return d->sentences;
}

static void allocateAndCopy(char* dest,const char* src) {
  }

DIALOUGE createDialouge(char** sentences, int count){
    DIALOUGE d = (DIALOUGE)malloc(sizeof(*d));
    if(!d) return NULL;
    d->top = count;
    d->sentences = malloc(sizeof(char*) * count);
    if(!d->sentences){ 
      free(d);
      return NULL;
    }

       
    for(int i = 0 ; i < count; i++) { 
      
    d->sentences[i] = malloc(sizeof(char) * strlen(sentences[i]) + 1);
    if(!d->sentences[i]) {
      fprintf(stderr, "Couldn't allocate memory for string");
      continue;
    }
    strcpy(d->sentences[i], sentences[i]);

    }
    return d;
}

void destroyDialouge(DIALOUGE dialouge){    
  free(dialouge);
}
