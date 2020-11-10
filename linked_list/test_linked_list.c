#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "linked_list.h"

// TO-DO: Write other tests
//        length, append, remove

bool run_tests() {
  int test_value = 3;
  node_t *test = ll_create(3);
  if (test == NULL) {
    printf("Test create failed\n");
    return false;
  }

  if (test->value != test_value) {
    printf("Test check value failed\n");
    return false;
  }

  node_t *found_node = ll_find(test, 7);
  if (found_node != test) {
    printf("Test find failed\n");
    return false;
  }

  return true;
}

int main(int argv, char *argc[]) {
  if (run_tests()) {
    printf("All tests passed!\n");
  } else {
    printf("Tests failed\n");
  }

  return 0;
}
