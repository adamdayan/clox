#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
  chunk->capacity = 0;
  chunk->count = 0;
  chunk->code = NULL;
  chunk->line = NULL;
  initValueArray(&chunk->constants);
}

// write 1 byte-code instruction to Chunk
void writeChunk(Chunk* chunk, const uint8_t byte, uint16_t line) {
  if ((chunk->capacity - chunk->count) == 0) {
    uint32_t oldCapacity = chunk->capacity;
    chunk->capacity = grow_capacity(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, chunk->capacity);
    chunk->line = GROW_ARRAY(uint16_t, chunk->line, chunk->capacity);
  }
  chunk->code[chunk->count] = byte;
  chunk->line[chunk->count] = line;
  chunk->count += 1;
}

// delete contents of chunk and re-initialise it
void freeChunk(Chunk* chunk) {
  FREE_ARRAY(uint8_t, chunk->code);
  FREE_ARRAY(uint16_t, chunk->line);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

// add a constant to the chunk
uint8_t addConstant(Chunk* chunk, const Value value) {
  writeValueArray(&chunk->constants, value);
  // return constant index so we can find it later
  return chunk->constants.count - 1;
}
