#include "../../headers/DialougeStorage.h"
#include "stdlib.h"

typedef DIALOUGE* DialougeStorage;

DialougeStorage initDialougeStorage() {
  DialougeStorage storage = (DialougeStorage)malloc(sizeof(DIALOUGE) * LAST_HOLDER);
  if(!storage) {
    return NULL;
  }
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

