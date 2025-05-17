#ifndef clox_vm_h
#define clox_vm_h

#include <stdio.h>

#include "chunk.h"
#include "common.h"

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR,
} InterpretResult;

typedef struct {
  Chunk* chunk;
  uint8_t* ip;
} Vm;

extern Vm vm;

void initVm();
void freeVm();
InterpretResult interpret(Chunk* chunk);

#endif
