#include "line.h"
#include "memory.h"

void initLineCounter(LineCounter* array) {
  array->count = 0;
  array->capacity = 0;
  array->offsets = NULL;
}

void writeNewLine(LineCounter* lines, const int offset) {
  if (lines->capacity == lines->count) {
    lines->capacity = grow_capacity(lines->capacity);
    lines->offsets = GROW_ARRAY(int, lines->offsets, lines->capacity);
  }
  lines->offsets[lines->count++] = offset;
}

void writeLineCounter(LineCounter* lines, const int offset, const int line) {
  // we've hit a new line
  if (offset == 0 || lines->count == line) {
    writeNewLine(lines, offset);
  } else {
    lines->offsets[lines->count - 1] = offset;
  }
}

int getLine(LineCounter* lines, int offset) {
  for (int current_line = 0; current_line < lines->count; current_line++) {
    if (lines->offsets[current_line] >= offset) {
      return current_line;
    }
  }
  return -1;
}

void freeLineCounter(LineCounter* lines) {
  FREE_ARRAY(int, lines->offsets);
  initLineCounter(lines);
}
