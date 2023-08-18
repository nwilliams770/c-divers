#include <stddef.h>

#define WSIZE 4        /* Word and header/footer size (bytes) */
#define DSIZE 8        /* Double word size (bytes) */
#define CHUNKSIZE (1<<12) /* Extend heap by this amount (bytes) */

#define MAX(x, y) ((x) > (y) ? (x) : (y))

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc) ((size) | (alloc))

/* Read and write a word at address p */
#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val))

/* Read the size and allocated fields from address p */
#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp) ((char *)(bp) - WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

/* Points to the heap prologue block header */
static void *heap_listp;
// Points to block where last search started
void *next_fit_startp;

static void *find_fit(size_t asize)
{
  void *bp;

  for (bp = next_fit_startp; ; bp = NEXT_BLKP(bp))
  {
    if (!GET_SIZE(HDRP(bp)))
    {
      // Reached the end of the heap without finding a suitable block
      // Continue search from beginning of heap
      bp = heap_listp;
    }

    if (!GET_ALLOC(HDRP(bp)) && asize <= GET_SIZE(HDRP(bp)))
    {
      // Suitable block found, update where next search should start
      next_fit_startp = NEXT_BLKP(bp);
      return bp;
    }

    if (bp == next_fit_startp)
    {
      // Entire heap searched and no suitable blocks, return
      return NULL;
    }
  }
}