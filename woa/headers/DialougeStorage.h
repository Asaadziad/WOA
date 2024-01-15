#ifndef DIALOUGESTORAGE_H
#define DIALOUGESTORAGE_H

#include "Dialouge.h"

typedef DIALOUGE* DialougeStorage;

// Dialouge storage is the data structure that will
// contain the dialouges
// initDialougeStorage - returns a DialougeStorage data structure 
DialougeStorage initDialougeStorage();

// destroyDialougeStorage - free's the memory allocated for the storage and its content
void destroyDialougeStorage(DialougeStorage d);

// getDialouge - searches for the requested dialouge and returns the response
// DialougeResponse - can be either a dialouge or an error
DialougeResponse getDialouge(DialougeStorage storage,DialougeRequest request);

// insertDialouge - adds a new dialouge to the storage.
void insertDialouge(DialougeStorage storage, DIALOUGE dialouge);

// returns the size of the storage.
int getDialougeStorageSize();

#endif
