#include <stdbool.h>

typedef struct node_t {
  int value;
  struct node_t *next;
} node_t;

node_t *ll_create(int value);
node_t *ll_find(node_t *root, int value);
unsigned int ll_length(node_t *root);
void ll_insert(node_t *root, int value);
bool ll_remove(node_t *root, int value);
bool ll_is_cyclic(node_t *root);

// To do ll_destroy_everything
