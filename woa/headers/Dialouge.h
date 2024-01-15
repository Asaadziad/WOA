#ifndef DIALOUGE_H
#define DIALOUGE_H


typedef struct dialouge_t* DIALOUGE;


// A request is the name of the dialouge
typedef enum {
  SWORD_DIALOUGE,
  MENU_DIALOUGE,
  LAST_HOLDER, // place holder to determine size of array
} DialougeRequest;

typedef enum {
  NULL_ARGS,
  ALLOCATION_ERROR,
  DIALOUGE_DOESNT_EXIST,
} DialougeError;

typedef union dialouge_res {
  DIALOUGE dialouge;
  DialougeError error;
} DialougeResponse;


DIALOUGE createDialouge(int id, char* dialouge);
void destroyDialouge(DIALOUGE dialouge);

#endif
