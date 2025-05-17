#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
  initVm();

  Chunk chunk;
  initChunk(&chunk);

  uint16_t constant = addConstant(&chunk, 42.0);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  constant = addConstant(&chunk, 8.0);
  writeChunk(&chunk, OP_CONSTANT, 124);
  writeChunk(&chunk, constant, 124);

  writeChunk(&chunk, OP_ADD, 124);

  constant = addConstant(&chunk, 2.0);
  writeChunk(&chunk, OP_CONSTANT, 125);
  writeChunk(&chunk, constant, 125);

  writeChunk(&chunk, OP_DIVIDE, 125);

  writeChunk(&chunk, OP_RETURN, 125);

  disassembleChunk(&chunk, "test chunk");
  interpret(&chunk);

  freeChunk(&chunk);
  freeVm();

  return 0;
}
