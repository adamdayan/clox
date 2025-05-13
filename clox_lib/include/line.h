#ifndef clox_line_h
#define clox_line_h

#include "common.h"

typedef struct {
  // current line
  uint16_t count;
  uint16_t capacity;
  // array of per-line offsets
  int* offsets;
} LineCounter;

void initLineCounter(LineCounter* lines);
void writeNewLine(LineCounter* lines, const int offset);
void writeLineCounter(LineCounter* lines, const int offset, const int line);
int getLine(LineCounter* lines, int offset);
void freeLineCounter(LineCounter* lines);

#endif
