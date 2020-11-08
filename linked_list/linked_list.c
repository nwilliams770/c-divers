#include <stdlib.h>
#include "linked_list.h"

node_t *ll_create(int value) {
  node_t *node = (node_t *)malloc(sizeof(node_t));
  if (node != NULL) {
    node->value = value;
  }

  return node;
}

node_t *ll_find(node_t *root, int value) {
  return root;
}

unsigned int ll_length(node_t *root) {
  return 0;
}

void ll_insert(node_t *root, int value) {

}

bool ll_remove(node_t *root, int value) {
  return true;
}

bool ll_is_cyclic(node_t *root) {
  return false;
}
