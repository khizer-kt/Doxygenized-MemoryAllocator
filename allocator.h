#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdlib.h>

void init_allocator(size_t pool_size);
void* my_malloc(size_t size);
void my_free(void* ptr);
void print_free_blocks();

#endif /* ALLOCATOR_H */
