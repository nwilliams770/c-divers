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
  // if NULL, return
  // if found, stop searching and return it
  // if not found, return NULL
  while (root) {
    if (root->value == value) {
      break;
    }

    root = root->next;
  }
  return root;
}

unsigned int ll_length(node_t *root) {
  int length = 0;

  while (root) {
    length++;
    root = root->next;
  }

  return length;
}

bool ll_append(node_t *root, int value) {
  while (root) {
    if (root->next == NULL) {
      node_t *node = ll_create(value);
      root->next = node;
      return true;
    }

    root = root->next;
  }

  // if input is NULL
  return false;
}

node_t *ll_remove(node_t *root, int value) {
  if (root == NULL) {
    return NULL;
  }

  node_t *node = root;
  node_t *prev_node = NULL;

  while (node) {
    if (node->value == value) {
        // head is val to remove
        if (prev_node == NULL) {
          root->value = node->value;
          root->next = node->next;
          free(root);
          return node;
        } else {
          prev_node->next = node->next;
          free(node);
          return root;
        }
    }
    prev_node = node;
    node = node->next;
  }

  return NULL;
}
