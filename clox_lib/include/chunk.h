#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "line.h"
#include "value.h"

typedef enum {
  OP_RETURN,
  OP_CONSTANT,
} OpCode;

typedef struct {
  uint32_t capacity;
  uint32_t count;
  uint8_t* code;
  LineCounter lines;
  ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, const uint8_t byte, uint16_t line);
void freeChunk(Chunk* chunk);
uint8_t addConstant(Chunk* chunk, const Value value);

#endif
