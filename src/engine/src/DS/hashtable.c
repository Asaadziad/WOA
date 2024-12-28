/*
 * Hashtable implementing the seperate chaining solution for collision
 * */

#include "headers/hashtable.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define INITIAL_LEN 10

typedef struct entry_t* Entry;

struct entry_t {
  char*   key;
  void*   value;
  Entry   next;
  size_t  hashvalue;
  size_t  hashvalue_mod;
};

Entry createEntry(void* key, void* value) {
  Entry entry = NULL;
  if(!key || !value){
    fprintf(stderr,"Null Arguments");
    return entry;
  } 

  entry = (Entry)malloc(sizeof(*entry));
  if(!entry) {
    fprintf(stderr, "Couldn't Allocate memory for Entry");
    return entry;
  } 
  
  entry->key   = key;
  entry->value = value; 
  entry->next  = NULL;
  return entry;
}

void destroyEntry(Entry e) {
  e->next = NULL;
  free(e);
}

struct hashtable_t {
  size_t size;
  Entry* entries; // Array of ptrs to lists
  void (*printElement)(Entry);
};


// Allocates memory and returns an empty table
HashTable createTable() {
  HashTable t = (HashTable)malloc( sizeof(*t) );
  if(!t) return NULL;
  
  t->entries = malloc(sizeof(Entry) * INITIAL_LEN);
  if(!t->entries) return NULL;
  
  t->size = 0;
  
  return t;
}

void destroyTable(HashTable table) {
  for(int i = 0; i < table->size; i++) {
    Entry current = table->entries[i];
    while(current) {
      Entry tmp = current->next;
      destroyEntry(current);
      current = tmp;
    } 
  }
  free(table);
}

size_t tableGetSize(HashTable table) {
  if(!table) return 0;
  return table->size;
}


long hash(char* key) {

	long hashVal = 0;

	while (*key != '\0') {

		hashVal = (hashVal << 4) + *(key++);

		long g = hashVal & 0xF0000000L;

		if (g != 0) hashVal ^= g >> 24;

		hashVal &= ~g;

	}

	return hashVal;

}		

void
tableInsert(HashTable table, KEY key, void* value) {
  if(!key || !value || !table) {
    fprintf(stderr, "NULL Argument");
    return;
  } 
  long _hash = hash(key);
  int hashval = _hash % INITIAL_LEN;
  Entry tmpHead = table->entries[hashval];
  table->entries[hashval] = createEntry(key, value);
  table->entries[hashval]->next = tmpHead;
  table->entries[hashval]->hashvalue_mod = hashval;
  table->entries[hashval]->hashvalue = _hash;
  
}

void* 
tableSearch(HashTable table, KEY key) {
  if(!table || !key) return NULL;
  long _hash = hash(key);
  int hashVal = _hash % INITIAL_LEN;
  Entry current = table->entries[hashVal];
  while(current) {
    if(strcmp(key, current->key) == 0) {
      return current->value;
    }
    current = current->next;
  }

  return NULL;
}

void
tableDelete(HashTable table, KEY key) {
  if(!table || !key) return;
  long _hash = hash(key);
  int hashVal = _hash % INITIAL_LEN;
  Entry current = table->entries[hashVal];
  Entry prev = NULL;
  if(!current->next) {
    destroyEntry(current);
    table->entries[hashVal] = NULL;
    return;
  }
  while(current) {
    Entry tmp = current->next;
    if(strcmp(key, current->key) == 0) {
      if(!prev) {
        table->entries[hashVal] = current->next;
        destroyEntry(current);
        return;
      }
      prev->next = current->next;
      destroyEntry(current);
      return;
    }
    prev = current;
    current = tmp;
  }

}

void tablePrint(HashTable table) {
  printf("\n");
  for(int i = 0; i < INITIAL_LEN ; i++) {
    Entry current = table->entries[i];
    while(current) {
      Entry tmp = current->next;
      printf("{ %s : %p } hashvalue: %zu hashvalue_mod: %zu\n ", current->key, current->value, current->hashvalue, current->hashvalue_mod);
      current = tmp;
    }
  }
}


