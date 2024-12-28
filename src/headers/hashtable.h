#ifndef HASHTABLE_C
#define HASHTABLE_C

#include "stddef.h"

typedef char* KEY;

// Bundle the data
typedef struct hashtable_t* HashTable;

// Initialization and Destroying
HashTable createTable();
void      destroyTable(HashTable table);

// Methods
size_t  tableGetSize(HashTable table);
void    tableInsert(HashTable table, KEY key, void* value);
void*   tableSearch(HashTable table, KEY key);
void    tableDelete(HashTable table, KEY key);

// prints the whole table as { key : value } 
void tablePrint(HashTable table);
#endif
