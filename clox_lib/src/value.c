#include <stdio.h>

#include "memory.h"
#include "value.h"

void initValueArray(ValueArray* array) {
  array->count = 0;
  array->capacity = 0;
  array->values = NULL;
}

void writeValueArray(ValueArray* array, const Value value) {
  if (array->capacity == array->count) {
    array->capacity = grow_capacity(array->capacity);
    array->values = GROW_ARRAY(Value, array->values, array->capacity);
  }
  array->values[array->count++] = value;
}

void freeValueArray(ValueArray* array) {
  FREE_ARRAY(Value, array->values);
  initValueArray(array);
}

void printValue(Value value) { printf("%g", value); }
