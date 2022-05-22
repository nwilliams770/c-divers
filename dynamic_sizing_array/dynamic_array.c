#include <stdlib.h>
#include "dynamic_array.h"

dynamic_array *da_create(int *initial_contents, int initial_contents_len) {
  dynamic_array *da = malloc(sizeof(dynamic_array));
  if (da == NULL) {
    return NULL;
  }

  if (initial_contents == NULL || initial_contents_len == 0) {
    int *contents = malloc(sizeof(int) * 10);
    if (contents == NULL) {
      return NULL;
    }
    da->contents = contents;
    da->length = 0;
    da->capacity = 10;
    return da;
  }

  int *contents = malloc(sizeof(int) * initial_contents_len * 2);
  if (contents == NULL) {
    return NULL;
  }
  for (int i = 0; i < initial_contents_len; i++) {
    contents[i] = initial_contents[i];
  }
  da->contents = contents;
  da->length = initial_contents_len;
  da->capacity = initial_contents_len * 2;

  return da;
}

int da_destroy(dynamic_array *da) {
  if (da == NULL) {
    return 1;
  }

  free(da);
  return 0;
}

unsigned int da_len(dynamic_array *da) {
  if (da == NULL) {
    return 1;
  }
  return da->length;
}

int da_push(dynamic_array *da, int value) {
  if (da == NULL) {
    return 1;
  }

  if (da->capacity == da->length) {
    int err = da_resize(da);
    if (err) {
      return err;
    }
  }

  da->contents[da->length] = value;
  da->length++;
  return 0;
}

int da_pop(dynamic_array *da, int *value) {
  if (da == NULL || da->length == 0) {
    return 1;
  }

  *value = da->contents[da->length - 1];
  da->length--;
  return 0;
}

int da_unshift(dynamic_array *da, int value) {
  if (da == NULL) {
    return 1;
  }

  if (da->capacity == da->length) {
    int err = da_resize(da);
    if (err) {
      return err;
    }
  }

  for (int i = da->length; i > 0; i--) {
    da->contents[i - 1] = da->contents[i];
  }

  da->contents[0] = value;
  da->length++;
  return 0;
}

int da_shift(dynamic_array *da, int *value) {
  if (da->length == 0) {
    return 1;
  }

  *value = da->contents[0];
  for (int i = 1; i < da->length - 1; i++) {
    da->contents[i - 1] = da->contents[i];
  }

  return value;
}

int da_resize(dynamic_array *da) {
  int new_capacity = da->capacity * 2;
  int *new_contents = malloc(sizeof(int) * new_capacity);
  if (new_contents == NULL) {
    return 1;
  }

  for (int i = 0; i < da->length; i++) {
    new_contents[i] = da->contents[i];
  }

  free(da->contents);
  da->contents = new_contents;
  da->capacity = new_capacity;

  return 0;
}