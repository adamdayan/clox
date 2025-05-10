#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;

typedef struct {
  uint16_t count;
  uint16_t capacity;
  Value* values;
} ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, const Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif
