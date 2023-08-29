#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/heap.h"

#define CAPACITY 15
#define _parent_idx_(idx) ((idx - 1) / 2)
#define _left_child_idx_(idx) (2 * idx + 1)
#define _right_child_idx_(idx) (2 * idx + 2)

typedef struct HeapNode {
    void* data;
    double priority;
    int arr_idx;
} HeapNode;

typedef struct Heap {
    HeapNode* nodes;
    int size;
    int capacity;
    void (*destructor_fn)(void*, ...);
    int (*cmp)(void*, void*);
} Heap;

void node_swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
    temp.arr_idx = a->arr_idx;
    a->arr_idx = b->arr_idx;
    b->arr_idx = temp.arr_idx;
}

void heapify_up(Heap* heap, int idx) {
    if (idx == 0) {
        return;
    }

    HeapNode* current = &heap->nodes[idx];
    HeapNode* parent = &heap->nodes[_parent_idx_(idx)];

    if (current->priority < parent->priority) {
        node_swap(current, parent);
        heapify_up(heap, _parent_idx_(idx));
    }
}

void heapify_down(Heap* heap, int idx) {
    int left_child_idx = _left_child_idx_(idx);
    int right_child_idx = _right_child_idx_(idx);
    int smallest = idx;

    if (left_child_idx < heap->size &&
        heap->nodes[left_child_idx].priority < heap->nodes[smallest].priority) {
        smallest = left_child_idx;
    }

    if (right_child_idx < heap->size &&
        heap->nodes[right_child_idx].priority < heap->nodes[smallest].priority) {
        smallest = right_child_idx;
    }

    if (smallest != idx) {
        node_swap(&heap->nodes[idx], &heap->nodes[smallest]);
        heapify_down(heap, smallest);
    }
}

Heap* heap_construct(void (*DatatypeDestructorFn)(void *, ...), int (*cmp)(void*, void*)) {
    Heap* heap = malloc(sizeof(Heap));
    heap->size = 0;
    heap->capacity = CAPACITY;
    heap->nodes = malloc(sizeof(HeapNode) * heap->capacity);
    heap->destructor_fn = DatatypeDestructorFn;
    heap->cmp = cmp;
    return heap;
}

void* heap_find(Heap* heap, void* data) {
    for (int i = 0; i < heap->size; i++) {
        if(data != NULL && heap->nodes[i].data != NULL)
            if (heap->cmp(heap->nodes[i].data, data) == 0) {
                return &heap->nodes[i];
            }
    }
    return NULL;
}

void heap_push(Heap* heap, void* data, double priority) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->nodes = realloc(heap->nodes, sizeof(HeapNode) * heap->capacity);
    }

    HeapNode* node = heap_find(heap, data);
    if(node != NULL) {
        if(node->priority > priority)
            node->priority = priority;
            heapify_up(heap, node->arr_idx);
            heap->destructor_fn(data);
            return;
    }

    heap->nodes[heap->size].data = data;
    heap->nodes[heap->size].priority = priority;
    heap->size++;

    if (heap->size == 1) {
        heap->nodes[0].arr_idx = 0;
        return;
    }

    heap->nodes[heap->size - 1].arr_idx = heap->size - 1;
    heapify_up(heap, heap->size - 1);
}

HeapNode* heap_left_child_node(Heap* heap, HeapNode* node) {
    return &heap->nodes[_left_child_idx_(node->arr_idx)];
}

HeapNode* heap_right_child_node(Heap* heap, HeapNode* node) {
    return &heap->nodes[_right_child_idx_(node->arr_idx)];
}

HeapNode* heap_parent_node(Heap* heap, HeapNode* node) {
    return &heap->nodes[_parent_idx_(node->arr_idx)];
}

int heap_empty(Heap* heap) {
    return heap->size == 0;
}

void* heap_min(Heap* heap) {
    return heap->nodes[0].data;
}

double heap_min_priority(Heap* heap) {
    return heap->nodes[0].priority;
}

void* heap_pop(Heap* heap) {
    if (heap->size == 0) {
        return NULL;
    }

    void* data = heap->nodes[0].data;
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;

    heapify_down(heap, 0);

    return data;
}

void heap_destroy(Heap* heap) {
    for (int i = 0; i < heap->size; i++) {
        heap->destructor_fn(heap->nodes[i].data);
    }
    free(heap->nodes);
    free(heap);
}

void heap_sort(Heap* heap) {
    void (*DatatypeDestructorFn)(void *, ...) = heap->destructor_fn;
    int (*cmp)(void*, void*) = heap->cmp;
    Heap* temp = heap_construct(DatatypeDestructorFn, cmp);
    memcpy(temp->nodes, heap->nodes, sizeof(HeapNode) * heap->size);
    temp->size = heap->size;

    for (int i = 0; i < heap->size; i++) {
        heap->nodes[i] = temp->nodes[0];
        heap_pop(temp);
    }
    heap_destroy(temp);
}

void heap_print(Heap* heap, void (*print_fn)(void*)) {
    int i = 0;
    for (i = 0; i < heap->size; i++) {
        print_fn(heap->nodes[i].data);
    }
    printf("\n");
}

void heap_tree_print(Heap* heap, void (*print_fn)(void*)) {
    int i = 0;
    printf("\n===[ Heap tree ]===\n");
    for (i = 0; i < heap->size; i++) {
        HeapNode* node = &heap->nodes[i];
        HeapNode* left_child = heap_left_child_node(heap, node);
        HeapNode* right_child = heap_right_child_node(heap, node);
        HeapNode* parent = heap_parent_node(heap, node);

        printf("Node: ");
        if(node->data != NULL)
            print_fn(node->data);
            
        printf(" Left child: ");
        if(left_child->data != NULL)
            print_fn(left_child->data);
        else
            printf("NULL");

        printf(" Right child: ");
        if(right_child->data != NULL)
            print_fn(right_child->data);
        else
            printf("NULL");

        printf(" Parent: ");
        if(parent->data != NULL)
            print_fn(parent->data);
        else
            printf("NULL");
        printf("\n");
    }
}