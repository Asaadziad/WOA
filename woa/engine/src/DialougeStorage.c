#include "../../headers/DialougeStorage.h"


#include "stdlib.h"

typedef DIALOUGE* DialougeStorage;

extern char* dialouges[][LAST_HOLDER];
extern int dialougesLen[LAST_HOLDER];

static void  fillStorage(DialougeStorage storage){
  
 for (int i = 0; i < LAST_HOLDER;i++) {
    storage[i] = createDialouge(dialouges[i], dialougesLen[i]);
 
 } 
  

}

DialougeStorage initDialougeStorage() {
  DialougeStorage storage = (DialougeStorage)malloc(sizeof(DIALOUGE) * LAST_HOLDER);
  if(!storage) {
    return NULL;
  }
  fillStorage(storage);
  return storage;
}


void destroyDialougeStorage(DialougeStorage d) {
  if(!d) return;
  free(d);
}


DialougeResponse getDialouge(DialougeStorage storage,DialougeRequest request){
  DialougeResponse res;
  if(request.dialougeName < 0 || request.dialougeName >= LAST_HOLDER) {
    res.error  = NULL_ARGS;
    res.dialouge = NULL;
    return res;
  }
  res.error = DIALOUGE_SUCCESS;
  res.dialouge = storage[request.dialougeName];
  return res;
}

// insertDialouge - adds a new dialouge to the storage.
void insertDialouge(DialougeStorage storage, DIALOUGE dialouge) { 
  return;
}

// returns the size of the storage.
int getDialougeStorageSize() {
  return LAST_HOLDER;
}

