#ifndef MEMORY_H
#define MEMORY_H

#include "stddef.h"

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, arrayPointer, oldCount, newCount) \
    (type*)reallocate(arrayPointer, sizeof(type) * oldCount, sizeof(type) * newCount)

#define FREE_ARRAY(type, arrayPointer, capacity) (type*)reallocate(arrayPointer, sizeof(type) * capacity, 0)

#define ALLOCATE(type, count) \
    (type*)reallocate(NULL, 0, sizeof(type) * (count))

     

void* reallocate(void* pointer, size_t old_size, size_t new_size);


#endif
