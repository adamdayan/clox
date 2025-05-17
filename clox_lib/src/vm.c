#include "vm.h"
#include "debug.h"

#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

Vm vm;

void initVm() {}

void freeVm() {}

InterpretResult run() {
  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
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
      printValue(READ_CONSTANT());
      printf("\n");
    }
  }
}

InterpretResult interpret(Chunk* chunk) {
  vm.chunk = chunk;
  vm.ip = chunk->code;

  return run();
}

#undef READ_BYTE
#undef READ_CONSTANT
