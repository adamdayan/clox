#include <stdio.h>

#include "debug.h"
#include "vm.h"

#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op)                                                          \
  do {                                                                         \
    Value b = pop();                                                           \
    Value a = pop();                                                           \
    push(a op b);                                                              \
  } while (false)

Vm vm;

void initVm() { resetStack(); }

void freeVm() {}

InterpretResult run() {
  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    // print the current contents of the stack
    printf("   ");
    for (Value* slot = vm.stack; slot < vm.stack_top; slot++) {
      printf("[ ");
      printValue(*slot);
      printf(" ]");
    }
    printf("\n");

    // if we're debugging, disassemble the instruction before running it
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

    // decode the instruction and then execute it based on the opcode
    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
      case OP_RETURN:
        return INTERPRET_OK;
      case OP_CONSTANT:
        printf("    ");
        Value constant = READ_CONSTANT();
        printValue(constant);
        printf("\n");
        push(constant);
        break;
      case OP_NEGATE:
        push(-pop());
        break;
      case OP_ADD:
        BINARY_OP(+);
        break;
      case OP_SUBTRACT:
        BINARY_OP(-);
        break;
      case OP_MULTIPLY:
        BINARY_OP(*);
        break;
      case OP_DIVIDE:
        BINARY_OP(/);
        break;
      default: {
        printf("Unknown instruction!");
        return INTERPRET_RUNTIME_ERROR;
      }
    }
  }
}

InterpretResult interpret(Chunk* chunk) {
  vm.chunk = chunk;
  vm.ip = chunk->code;

  return run();
}

// reset VM stack pointer
void resetStack() { vm.stack_top = vm.stack; }

// push a Value onto the VM stack
void push(Value value) {
  (*vm.stack_top) = value;
  vm.stack_top++;
}

// pop a Value from the VM stack
Value pop() { return (*--vm.stack_top); }

#undef READ_BYTE
#undef READ_CONSTANT
