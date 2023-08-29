#ifndef _HEAP_H_
#define _HEAP_H_

#define true 1
#define false 0

typedef int Bool;
typedef struct Heap Heap;

Heap *heap_construct(void (*DatatypeDestructorFn)(void *, ...), int (*cmp)(void*, void*)); // O(1)
void heap_push(
Heap *heap, void *data, double priority); // O(log N)
Bool heap_empty(Heap *heap); // O(1)
void *heap_max(Heap *heap); // O(1)
double heap_min_priority(Heap *heap); // O(1)
void *heap_pop(Heap *heap); // O(log N)
void heap_destroy(Heap *heap); // O(1)
void heap_sort(Heap *heap); // O(N log N)
void* heap_find(Heap* heap, void* data);

void heap_print(Heap *heap, void (*print_fn)(void *));
void heap_tree_print(Heap* heap, void (*print_fn)(void*)) ;

typedef struct HeapNode HeapNode;
HeapNode* heap_left_child_node(Heap *heap, HeapNode *node);
HeapNode* heap_right_child_node(Heap *heap, HeapNode *node);
HeapNode* heap_parent_node(Heap *heap, HeapNode *node);
#endif