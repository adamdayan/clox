#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
  OP_RETURN,
  OP_CONSTANT,
  // unary arithmetic operators
  OP_NEGATE,
  // binary arithmetic operators
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
} OpCode;

typedef struct {
  uint32_t capacity;
  uint32_t count;
  uint8_t* code;
  uint16_t* line;
  ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, const uint8_t byte, uint16_t line);
void freeChunk(Chunk* chunk);
uint8_t addConstant(Chunk* chunk, const Value value);

#endif
