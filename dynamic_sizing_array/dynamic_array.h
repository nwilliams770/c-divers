#include <stdbool.h>

typedef struct dynamic_array {
  unsigned int capacity;
  unsigned int length;
  int *contents;
} dynamic_array;

// Maybe instead of bools these should return an int (1 - success, 0 - fail)
// so don't have to bring in stdbool lib
dynamic_array *da_create(int *initial_contents, int initial_contents_len);
int da_destroy(dynamic_array *da);
unsigned int da_len(dynamic_array *da);
int da_push(dynamic_array *da, int value);
int da_pop(dynamic_array *da, int *value);
int da_unshift(dynamic_array *da, int value);
int da_shift(dynamic_array *da, int *value);
int da_resize(dynamic_array *da);
