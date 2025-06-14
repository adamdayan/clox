#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "common.h"

#define STACK_MAX 256

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR,
} InterpretResult;

// Virtual Machine responsible for holding program state and executing code
// Chunks
typedef struct {
  // code chunk currently being executed
  Chunk* chunk;
  // instruction pointer
  uint8_t* ip;
  // stack memory
  Value stack[STACK_MAX];
  // stack pointer
  Value* stack_top;
} Vm;

extern Vm vm;

void initVm();
void freeVm();
InterpretResult interpret(char* source);
// stack methods
void resetStack();
void push(Value value);
Value pop();

#endif
