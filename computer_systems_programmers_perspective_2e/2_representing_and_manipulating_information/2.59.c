#include <stdlib.h>

void merge_bytes(size_t x, size_t y) {
  x &= 0xff;
  y &= ~0xff;
  return x | y;
  // return (x & 0xff) | (y & ~0xff);
}