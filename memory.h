#ifndef MEMORY_H
#define MEMORY_H

#include "stddef.h"

#define FREE_ARRAY(type, arrayPointer, capacity) (type*)reallocate(arrayPointer, sizeof(type) * capacity, 0)

#define ALLOCATE(type, count) \
    (type*)reallocate(NULL, 0, sizeof(type) * (count))



void* reallocate(void* pointer, size_t old_size, size_t new_size);

#endif