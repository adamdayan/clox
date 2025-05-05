#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

static inline uint32_t grow_capacity(const uint32_t old_capacity) {
  return (old_capacity < 8) ? 8 : old_capacity * 2;
}

// NOTE: consider making this an inline function because I hate
// these macros
#define GROW_ARRAY(type, pointer, newCapacity)                                 \
  (type*)reallocate(pointer, sizeof(type) * newCapacity)

#define FREE_ARRAY(type, pointer) (type*)reallocate(pointer, 0)

void* reallocate(void* pointer, size_t newSize);

#endif
