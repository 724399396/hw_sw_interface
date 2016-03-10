/*
Coursera HW/SW Interface
Lab 4 - Mystery Caches

Mystery Cache Geometries (for you to keep notes):
mystery0:
    block size =
    cache size =
    associativity =
mystery1:
    block size =
    cache size =
    associativity =
mystery2:
    block size =
    cache size =
    associativity =
mystery3:
    block size =
    cache size =
    associativity =
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real"
 * memory addresses. You can use any convenient integer value as a
 * memory address, you should not be able to cause a segmentation
 * fault by providing a memory address out of your programs address
 * space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  /* YOUR CODE GOES HERE */
  flush_cache();
  addr_t ptr = 0x1374310000000000;
  int size = 0;
  bool_t get;
  access_cache(ptr);
  do {
    size++;
    get = access_cache(ptr+size);
  } while (get);
  return size;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int size) {
  /* YOUR CODE GOES HERE */
  addr_t ptr = 0x1374310000000000;
  unsigned long long block_num = 0;
  while (1) {
    flush_cache();
    unsigned long long i = 0;
    for(; i <= block_num; i++) {
      access_cache(ptr+i);
    }
    if (access_cache(ptr)) {
	block_num++;
    } else {
	break;
    }
  }
  return block_num * get_block_size();
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int size) {
  /* YOUR CODE GOES HERE */
  int block_size = get_block_size();
  int cache_size = get_cache_size(0);
  int assoc = 1;
  int step_size = cache_size / block_size;
  addr_t ptr =  0x1374310000000000;
  while(1) {
    flush_cache();
    int step;
    for(step = 0; step <= assoc; step++)
      access_cache(ptr+step*step_size);
    if(access_cache(ptr)) {
      assoc++;
    } else {
      break;
    }
  }
  return assoc;
}

//// DO NOT CHANGE ANYTHING BELOW THIS POINT
int main(void) {
  int size;
  int assoc;
  int block_size;

  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.  You can
     test your geometry paramter discovery routines by calling
     cache_init() w/ your own size and block size values. */
  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
