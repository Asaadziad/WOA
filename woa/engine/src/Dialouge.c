#include "../../headers/Dialouge.h"
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
      strcpy(d->sentences[i], sentences[i]);
    }
    return d;
}

void destroyDialouge(DIALOUGE dialouge){    
  free(dialouge);
}
