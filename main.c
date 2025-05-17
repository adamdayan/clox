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
  writeChunk(&chunk, OP_RETURN, 123);
  writeChunk(&chunk, OP_RETURN, 124);

  disassembleChunk(&chunk, "test chunk");

  freeChunk(&chunk);

  freeVm();

  return 0;
}
