#ifndef DIALOUGE_H
#define DIALOUGE_H

#include "SDL2/SDL.h"

typedef struct dialouge_t* DIALOUGE;

typedef enum {
  NULL_ARGS,
  ALLOCATION_ERROR,
  DIALOUGE_DOESNT_EXIST,
  DIALOUGE_SUCCESS,
} DialougeError;

typedef struct dialouge_res {
  DIALOUGE dialouge;
  DialougeError error;
} DialougeResponse;

typedef struct dialoge_req {
  enum {
  // MULTI-LINE DIALOUGES HERE
  SWORD_DIALOUGE,
  MENU_DIALOUGE,
  
  //Singular Texts here
  HP_TEXT,
  LAST_HOLDER, // place holder to determine size of array
  } dialougeName;
  
  // font stuff
  int      fontHeight;
  int      fontWidth;
  SDL_Color fontColor;
} DialougeRequest;

DIALOUGE createDialouge(char** sentences, int count);
void destroyDialouge(DIALOUGE dialouge);


//getters
int getSentencesCount(DIALOUGE d);
char** getSentences(DIALOUGE d);


#endif
