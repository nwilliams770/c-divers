#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "dynamic_array.h"

bool run_tests() {
  // ***** da_create *****
  int test_initial_contents[3] = {1, 2, 3};
  int test_initial_contents_len = 3;
  dynamic_array *test_da = da_create(test_initial_contents, test_initial_contents_len);
  if (test_da == NULL) {
    printf("Test da_create failed -- create dynamic_arrays\n");
    return false;
  }

  // ***** da_len *****
  int err = da_len(NULL);
  if (!err) {
    printf("Test da_len failed -- NULL pointer \n");
    return false;
  }

  int test_len = da_len(test_da);
  if (test_len != test_initial_contents_len) {
    printf("Test da_len failed -- Expected: %i, Actual: %i \n", test_initial_contents_len, test_len);
    return false;
  }
}