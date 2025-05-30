#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
  printf("== %s ==\n", name);

  for (uint32_t offset = 0; offset < chunk->count;) {
    offset = disassembleInstruction(chunk, offset);
  }
}

static int simpleInstruction(const char* name, const int offset) {
  printf("%s\n", name);
  return offset + 1;
}

static int constantInstruction(const char* name, const Chunk* chunk,
                               const int offset) {
  uint8_t constant_idx = chunk->code[offset + 1];
  printf("%-16s %4d '", name, constant_idx);
  printValue(chunk->constants.values[constant_idx]);
  printf("'\n");
  return offset + 2;
}

int disassembleInstruction(Chunk* chunk, const int offset) {
  printf("%04d ", offset);
  // if this is an instruction on a newline, print the line number otherwise
  // print '|'
  if (offset > 0 && chunk->line[offset] == chunk->line[offset - 1]) {
    printf("   | ");
  } else {
    printf("%4d ", chunk->line[offset]);
  }

  uint8_t instruction = chunk->code[offset];
  switch (instruction) {
    case OP_RETURN:
      return simpleInstruction("OP_RETURN", offset);
    case OP_NEGATE:
      return simpleInstruction("OP_NEGATE", offset);
    case OP_ADD:
      return simpleInstruction("OP_ADD", offset);
    case OP_SUBTRACT:
      return simpleInstruction("OP_SUBTRACT", offset);
    case OP_MULTIPLY:
      return simpleInstruction("OP_MULTIPLY", offset);
    case OP_DIVIDE:
      return simpleInstruction("OP_DIVIDE", offset);
    case OP_CONSTANT:
      return constantInstruction("OP_CONSTANT", chunk, offset);
    default:
      printf("unknown opcode: %d\n", instruction);
      return offset + 1;
  }
}
