#include "hashtable.h"
#include "stddef.h"

#define START_SIZE 8

typedef struct {
  KEY key;
  VAL value;
} Entry;

// TODO:: let the user define a destroy function
static void destroyEntry(Entry e){}

struct hash_t {
  size_t size;
  Entry* entries; 
};


// Creates an empty table of size - START_SIZE
HashTable createTable(){
  HashTable t = (HashTable)malloc(sizeof(*t));
  if(!t) return NULL;
  t->size = 0;
  t->entries = (Entry*)malloc(sizeof(Entry) * START_SIZE);
  if(!t->entries) return NULL;
  return t;
}

void destroyTable(HashTable table){
  if(!table) return;
  for(int i = 0;i < table->size;i++){
    destroyEntry(table->entries[i]);
  }
  free(table->entries);
  free(table);
}
