#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct hash_t* HashTable;
typedef void*          KEY;
typedef void*          VAL;

// Creates an empty table (allocates memory for new table)
HashTable createTable();
// free's the memory allocated for table
void      destroyTable(HashTable table);


// Table functionality.
bool tableAdd(HashTable table, KEY key, VAL value);
VAL  tableFind(HashTable table, KEY key);
VAL  tableDelete(HashTable table, KEY key);

#endif
