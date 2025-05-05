#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
  chunk->capacity = 0;
  chunk->count = 0;
  chunk->code = NULL;
}

// write 1 byte-code instruction to Chunk
void writeChunk(Chunk* chunk, const uint8_t byte) {
  if ((chunk->capacity - chunk->count) == 0) {
    uint32_t oldCapacity = chunk->capacity;
    chunk->capacity = grow_capacity(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, chunk->capacity);
  }
  chunk->code[chunk->count] = byte;
  ++chunk->count;
}

// delete contents of chunk and re-initialise it
void freeChunk(Chunk* chunk) {
  FREE_ARRAY(uint8_t, chunk->code);
  initChunk(chunk);
}
