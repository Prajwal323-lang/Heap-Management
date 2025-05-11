Custom Heap Memory Management System (First Fit Allocation)
This project implements a heap memory management system in C using the First Fit memory allocation strategy. It simulates dynamic memory allocation within a fixed-size heap (1024 bytes), closely modeling how low-level memory allocators work in real operating systems.

Features
First Fit Allocation:
Allocates memory by scanning the free list and selecting the first block large enough to satisfy the request, optimizing speed of allocation.

Block Splitting:
If a free block is larger than needed, it is split into an allocated block and a smaller free block to utilize heap space efficiently.

Memory Deallocation:
Frees a previously allocated block by marking it as available and merging adjacent free blocks to reduce fragmentation.

Free Block Merging (Coalescing):
Ensures contiguous free blocks are combined during deallocation to maintain larger allocatable spaces and reduce external fragmentation.

Heap Visualization:
The print_heap() function provides a detailed view of the current heap layout — showing the size and status (free/used) of each memory block — useful for debugging and learning purposes.
