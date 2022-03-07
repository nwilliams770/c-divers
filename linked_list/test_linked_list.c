#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "linked_list.h"

// TO-DO: Write other tests
//        length, append, remove

bool run_tests() {
  // ***** ll_create *****
  int test_value = 3;
  node_t *test_root = ll_create(3);
  if (test_root == NULL) {
    printf("Test ll_create failed -- create node\n");
    return false;
  }

  if (test_root->value != test_value) {
    printf("Test ll_create failed -- check value\n");
    return false;
  }

  // ***** ll_find *****
  node_t *found_node = ll_find(test_root, 3);
  if (found_node != test_root) {
    printf("Test ll_find failed -- find node that exists\n");
    return false;
  }

  found_node = ll_find(test_root, 99);
  if (found_node != NULL) {
    printf("Test ll_find failed -- find node that doesn't exist\n");
    return false;
  }

  // ***** ll_length *****
  int length = ll_length(test_root);
  if (length != 1) {
    printf("Test ll_length failed -- get length of ll\n");
    return false;
  }

  // ***** ll_append *****
  int test_append_value = 5;
  bool append_success = ll_append(test_root, test_append_value);
  if (append_success != true) {
    printf("Test ll_append failed -- append a node with a valid value\n");
    return false;
  }

  append_success = ll_append(test_root, NULL);
  if (append_success != false) {
    printf("Test ll_append failed -- append a node with an invalid value\n");
    return false;
  }

// ***** ll_remove *****
  node_t *test_remove = ll_remove(test_root, test_append_value);
  if (test_remove != test_root) {
    printf("Test ll_remove failed -- root not returned when attempting to remove node that exists\n");
    return false;
  }

  int test_nonexistent_node_value = 10;
  test_remove = ll_remove(test_root, test_nonexistent_node_value);
  if (test_remove != NULL) {
    printf("Test ll_remove failed -- NULL not returned when attempting to remove nonexistent node\n");
    return false;
  }

  // // ***** ll_destroy *****
  bool test_destroy = ll_destroy(test_root);
  if (test_destroy != true) {
    printf("Test ll_destroy failed -- failed to destroy ll that exists\n");
    return false;
  }

  test_destroy = ll_destroy(NULL);
  if (test_destroy != false) {
    printf("Test ll_destroy failed -- return false when given NULL pointer\n");
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
