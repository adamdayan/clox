#include <stdlib.h>

#include "common.h"

// change the amount of memory allocated at pointer
void* reallocate(void* pointer, size_t newSize) {
  // if we're reducing the size to 0, free all the memory and return a NULL
  // pointer
  if (newSize == 0) {
    free(pointer);
    return NULL;
  }
  // otherwise, realloc will handle the 3 remaining possible cases:
  // 1. we can allocate/grow our current allocation contiguously
  // 2. we cannot grow our current allocation continously and need to allocate
  // new memory and copy out existing array across
  // 3. we need to shrink our existing allocation
  void* result = realloc(pointer, newSize);

  // if result is null ptr then the memory allocation failed and we should exist
  // gracefully
  if (result == NULL) {
    exit(1);
  }
  return result;
}
