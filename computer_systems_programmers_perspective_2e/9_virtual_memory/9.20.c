#include <stdalign.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define block_info_t as an integer type that can store both size and allocation status
typedef uint32_t block_info_t;

// Extract size and allocation status from header/footer
#define GET_SIZE(header) ((header) & ~0x1)
#define GET_ALLOC(header) ((header) & 0x1)
// Pack size and allocation status into an integer
#define PACK(size, alloc) ((size) | (alloc))
// Min 1 byte stored + guard bytes
#define MIN_BLOCK_SIZE (offsetof(Block, data) + 1 + GUARD_BYTE_SIZE)

const char GUARD_BYTE_PATTERN = 0xAA;
const size_t GUARD_BYTE_SIZE = 1;
const size_t GUARD_BYTES_SIZE = GUARD_BYTE_SIZE * 2;

typedef struct Block {
  struct Block* next_block;
  struct Block* prev_block;
  block_info_t header;          // Block header containing size and allocation status
  char data[]; // Flexible array member for data, starts with size 1 and includes guard bytes
} Block;

// Memory pool
char memory_pool[1024];
Block* next_fit_startp;
static Block* heap_listp;

void* my_malloc(size_t size);
void my_free(void* ptr);
Block* find_fit(size_t size);
Block* place(Block* bp, size_t size);
void coalesce(Block* bp);

void init()
{
  Block* prologue_block, *epilogue_block, *first_usable_block;
  size_t prologue_epilogue_size, usable_block_size;

  prologue_epilogue_size = sizeof(Block);
  // Calculate the remaining size for the first usable block
  usable_block_size = sizeof(memory_pool) - (prologue_epilogue_size * 2) - sizeof(Block);

  // Clear the memory pool to initialize it to a known state (all zeros)
  memset(memory_pool, 0, sizeof(memory_pool));

  prologue_block = (Block*)memory_pool;
  *prologue_block = (Block){
    .next_block = (Block*)((char*)prologue_block + prologue_epilogue_size),
    .prev_block = NULL,
    .header = PACK(prologue_epilogue_size, 1),
  };
  heap_listp = prologue_block;

  epilogue_block = (Block*)((char*)prologue_block + prologue_epilogue_size + usable_block_size);
  *epilogue_block = (Block){
    .next_block = NULL, // End of heap
    .prev_block = prologue_block->next_block, // Point to the first usable block
    .header = PACK(0, 1) // Allocated, size 0
  };


  // Create and initialize the first usable block within the memory_pool using a compound literal
  first_usable_block = prologue_block->next_block;
  *first_usable_block = (Block){
      .next_block = epilogue_block, // Point to epilogue block
      .prev_block = prologue_block, // Point to prologue block
      .header = PACK(usable_block_size, 0) // Not allocated
  };

  // Initialize next fit block
  next_fit_startp = prologue_block;
}

size_t calculate_padding(size_t alignment, size_t current_size) {
  size_t offset = current_size % alignment;
  if (offset == 0)
  {
      return 0;
  }
  else
  {
      return alignment - offset;
  }
}

// Function to allocate memory with proper alignment and interface similar to malloc()
void* my_malloc(size_t size) {
  if (size <= 0)
  {
    return NULL;
  }
  size_t adjusted_size, block_size, alignment;
  Block* bp;

  alignment = alignof(Block);
  // Determine the alignment requirement for struct Block
  adjusted_size = size + calculate_padding(alignment, block_size) + GUARD_BYTES_SIZE;
  // Calculate the size needed for memory allocation, including padding for alignment
  block_size = offsetof(Block, data) + adjusted_size; // Size of Block struct up to data[]


  // Check if there is enough space in the memory pool
  if ((bp = find_fit(block_size)) == NULL) {
      // Not enough space
      return NULL;
  }

  bp = place(bp, adjusted_size);

  return bp->data;
}

void my_free(void* ptr)
{
  if (ptr == NULL)
  {
    return;
  }
  Block* bp;
  size_t size;

  bp = (Block*)((char *)ptr - offsetof(Block, data) - GUARD_BYTES_SIZE);
  size = GET_SIZE(bp->header);

  if (!GET_ALLOC(bp->header)) {
    // Block is already freed, return without processing.
    return;
  }

  if (
    memcmp((const void *)bp->data, &GUARD_BYTE_PATTERN, GUARD_BYTE_SIZE) != 0 ||
    memcmp((const void *)((char *)bp->data + size - GUARD_BYTE_SIZE), &GUARD_BYTE_PATTERN, GUARD_BYTE_SIZE) != 0
  )
  {
    // Corruption detected, log
    fprintf(stderr, "Error: memory corruption detected\n");
    exit(EXIT_FAILURE);
  }

  memset(bp->data, 0, size);
  bp->header = PACK(size, 0);
  coalesce(bp);
}

Block* find_fit(size_t size)
{
  // maintain refernece to last checked block
  // check this block then traverse
  Block* bp;

  for (bp = next_fit_startp; ; bp = bp->next_block)
  {
    if (!GET_SIZE(bp->header))
    {
      // Reached end of heap
      bp = heap_listp;
    }

    if (!GET_ALLOC(bp->header) && GET_SIZE(bp->header) >= size)
    {
      // Found fit
      next_fit_startp = bp->next_block;
      return bp;
    }

    if (bp == next_fit_startp)
    {
      // Searched entire heap, no fit
      return NULL;
    }
  }
}

Block* place(Block* bp, size_t size)
{
  size_t remaining_capacity = GET_SIZE(bp->header) - size;

  if (remaining_capacity >= MIN_BLOCK_SIZE)
  {
    Block* new_block = (Block*)((char *)bp + size);

    new_block->header = PACK(remaining_capacity, 0);


    new_block->next_block = bp->next_block;
    bp->next_block = new_block;
    new_block->prev_block = bp;

  }
  else
  {
    bp->header = PACK(size, 1);
  }
  // Set guard bytes at beginning and end of data
  memset(bp->data, GUARD_BYTE_PATTERN, GUARD_BYTE_SIZE);
  // Cast to do pointer arithmetic
  memset((char *)bp->data + size - GUARD_BYTE_SIZE, GUARD_BYTE_PATTERN, GUARD_BYTE_SIZE);

  return bp;
}

void coalesce(Block* bp)
{
  Block* next = bp->next_block;
  while (next && !GET_ALLOC(next->header))
  {
    bp->header = PACK(GET_SIZE(bp->header) + GET_SIZE(next->header), 0);
    if (next->next_block)
    {
      next->next_block->prev_block = bp;
      bp->next_block = next->next_block;
    }
    next = next->next_block;
  }

  Block* prev = bp->prev_block;
  while (prev && !GET_ALLOC(prev->header))
  {
    prev->header = PACK(GET_SIZE(bp->header) + GET_SIZE(prev->header), 0);
    if (bp->next_block)
    {
      bp->next_block->prev_block = prev;
    }
    prev->next_block = bp->next_block;

    bp = prev;
    prev = prev->prev_block;
  }
}

int main() {
  init();

  const int num_iterations = 10000;
  const size_t block_sizes[] = {16, 32, 64, 128, 256};

  clock_t start, end;
  double cpu_time_used;

  for (size_t i = 0; i < sizeof(block_sizes) / sizeof(block_sizes[0]); i++)
  {
    size_t block_size = block_sizes[i];
    printf("Testing block size: %zu\n", block_size);

    // Allocate and deallocate memory in a loop
    start = clock();
    for (int j = 0; j < num_iterations; j++) {
        void* ptr = my_malloc(block_size);
        if (ptr) {
            my_free(ptr);
        }
    }
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for %d iterations: %f seconds\n", num_iterations, cpu_time_used);

  }
  return 0;
}
