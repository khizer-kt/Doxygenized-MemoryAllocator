#include "allocator.h"
#include <cstdio>

// Your allocator implementation goes here

typedef struct Block {
    size_t size;
    struct Block* next;
} Block;

Block* memory_pool = NULL;

void init_allocator(size_t pool_size) {
    memory_pool = (Block*)malloc(pool_size);
    if (memory_pool == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
    memory_pool->size = pool_size - sizeof(Block);
    memory_pool->next = NULL;
}

void* my_malloc(size_t size) {
    Block* current = memory_pool;
    Block* prev = NULL;

    while (current != NULL) {
        if (current->size >= size) {
            if (current->size > size + sizeof(Block)) {
                Block* new_block = (Block*)((char*)current + sizeof(Block) + size);
                new_block->size = current->size - size - sizeof(Block);
                new_block->next = current->next;
                current->size = size;
                current->next = new_block;
            }
            if (prev == NULL) {
                memory_pool = current->next;
            } else {
                prev->next = current->next;
            }
            return (void*)(current + 1);
        }
        prev = current;
        current = current->next;
    }
    fprintf(stderr, "Error: Insufficient memory\n");
    return NULL;
}

void my_free(void* ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Error: Attempt to free NULL pointer\n");
        return;
    }
    Block* block = (Block*)((char*)ptr - sizeof(Block));
    block->next = memory_pool;
    memory_pool = block;
}

void print_free_blocks() {
    printf("Free Memory Blocks:\n");
    Block* current = memory_pool;
    while (current != NULL) {
        printf("Address: %p, Size: %zu\n", (void*)current, current->size);
        current = current->next;
    }
    printf("\n");
}
