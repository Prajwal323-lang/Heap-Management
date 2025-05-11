#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HEAP_SIZE 1024

typedef struct Block {
    size_t size;
    bool free;
    struct Block* next;
} Block;

static char heap[HEAP_SIZE];
static Block* free_list = (Block*)heap;

void init_heap() {
    free_list->size = HEAP_SIZE - sizeof(Block);
    free_list->free = true;
    free_list->next = NULL;
}

void* allocate(size_t size) {
    Block* curr = free_list;
    while (curr) {
        if (curr->free && curr->size >= size) {
            if (curr->size > size + sizeof(Block)) {
                Block* new_block = (Block*)((char*)curr + sizeof(Block) + size);
                new_block->size = curr->size - size - sizeof(Block);

                new_block->free = true;
                new_block->next = curr->next;
                curr->next = new_block;
            }
            curr->size = size;
            curr->free = false;
            return (char*)curr + sizeof(Block);
        }
        curr = curr->next;
    }
    return NULL;
}

void merge_free_blocks() {
    Block* curr = free_list;
    while (curr && curr->next) {
        if (curr->free && curr->next->free) {
            curr->size += curr->next->size + sizeof(Block);
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}

void free_mem(void* ptr) {
    if (!ptr) return;
    Block* block = (Block*)((char*)ptr - sizeof(Block));
    block->free = true;
    merge_free_blocks();
}

void print_heap() {
    Block* curr = free_list;
    while (curr) {
        printf("Block at %p | Size: %zu | Free: %d\n", (void*)curr, curr->size, curr->free);
        curr = curr->next;
    }

    printf("------------\n");
}




int main() {
    init_heap();
    printf("Initial Heap:\n");
    print_heap();
    
    void* p1 = allocate(100);
    void* p2 = allocate(200);
    void* p4 = allocate(50);
    printf("\nAfter Allocations:\n");
    print_heap();
    
    free_mem(p1);
    printf("\nAfter Freeing p1:\n");
    print_heap();

    void* p6 = allocate(100);
    print_heap();
    
    free_mem(p2);
    printf("\nAfter Freeing p2:\n");
    print_heap();

    free_mem(p4);
    print_heap();

    // void* p3 = allocate(1024);
    // if(p3 == NULL){
    //     printf("Not enough memory!!\n");
    // }
    // print_heap();

    // void* p4 = allocate(1);
    // print_heap();
    
    return 0;
}
