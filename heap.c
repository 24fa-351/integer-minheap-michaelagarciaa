#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

#define KEY_NOT_PRESENT -1

// Create a new heap with a given capacity
heap_t *heap_create(int capacity) {
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
    heap->data = (heap_node_t *)malloc(capacity * sizeof(heap_node_t));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Free the heap memory
void heap_free(heap_t *heap) {
    free(heap->data);
    free(heap);
}

// Return the current size of the heap
unsigned int heap_size(heap_t *heap) { 
    return heap->size; 
}

// Get the parent index of a given node
unsigned int heap_parent(unsigned int index) { 
    return (index - 1) / 2; 
}

// Get the left child index of a given node
unsigned int heap_left_child(unsigned int index) { 
    return 2 * index + 1; 
}

// Get the right child index of a given node
unsigned int heap_right_child(unsigned int index) { 
    return 2 * index + 2; 
}

// Calculate the level of a node in the heap
unsigned int heap_level(unsigned int index) {
    unsigned int level = 0;
    while (index > 0) {
        index = heap_parent(index);
        level++;
    }
    return level;
}

// Print the heap elements with their level and index
void heap_print(heap_t *heap) {
    for (int ix = 0; ix < heap_size(heap); ix++) {
        printf("%3d - %3d : " HEAP_KEY_FORMAT "\n", heap_level(ix), ix,
               heap->data[ix].key);
    }
    printf("\n");
}

// Swap two elements in the heap
void heap_swap(heap_t *heap, int index1, int index2) {
    heap_node_t temp = heap->data[index1];
    heap->data[index1] = heap->data[index2];
    heap->data[index2] = temp;
}

// Bubble up the element at a given index to restore the heap property
void heap_bubble_up(heap_t *heap, int index) {
    while (index > 0) {
        int parent_index = heap_parent(index);
        if (heap->data[parent_index].key <= heap->data[index].key) {
            break;
        }
        heap_swap(heap, parent_index, index);
        index = parent_index;
    }
}

// Bubble down the element at a given index to restore the heap property
void heap_bubble_down(heap_t *heap, int index) {
    int left = heap_left_child(index);
    int right = heap_right_child(index);
    int smallest = index;

    if (left < heap_size(heap) && heap->data[left].key < heap->data[smallest].key) {
        smallest = left;
    }
    if (right < heap_size(heap) && heap->data[right].key < heap->data[smallest].key) {
        smallest = right;
    }
    if (smallest != index) {
        heap_swap(heap, index, smallest);
        heap_bubble_down(heap, smallest);
    }
}

// Insert a new element into the heap
void heap_insert(heap_t *heap, heap_key_t key, heap_value_t data) {
    if (heap_size(heap) == heap->capacity) {
        return;
    }

    heap->data[heap_size(heap)].key = key;
    heap->data[heap_size(heap)].value = data;
    heap->size++;

    heap_bubble_up(heap, heap_size(heap) - 1);
}

// Remove and return the minimum element from the heap
heap_value_t heap_remove_min(heap_t *heap) {
    if (heap_size(heap) == 0) {
        return NULL;
    }

    heap_value_t min = heap->data[0].value;
    heap->size--;

    // Move last element to the root
    heap->data[0] = heap->data[heap_size(heap)];

    // Then bubble it down to its correct position
    heap_bubble_down(heap, 0);

    return min;
}
