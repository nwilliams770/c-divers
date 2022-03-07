#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "base64.h"

int main(int argc, char *argv[]) {
  size_t n_items = 1;
  // int *buffer = (int *)malloc(sizeof(int) * n_items);
  // buffer[0] = 0;
  int buffer[] = { 0 };
  char *output_str;
  base64_encode(buffer, sizeof(buffer[0]), n_items, &output_str);

  if (strcmp(output_str, "AAAA") != 0) {
    printf("FAILURE!\n\tExpected: 'AAAA'\n\tGot: %s\n", output_str);
  }

  return 0;
}
