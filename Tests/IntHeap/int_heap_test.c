#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Source/libs/headers/heap.h"

void destructor_fn(void* data, ...) {
    free(data);
}

int cmp(void* a, void* b) {
    return *(int*)a - *(int*)b;
}

void print_int(void* data) {
    printf("%d ", *(int*)data);
}

int main(){
    
    Heap* heap = heap_construct(destructor_fn, cmp);
    int** arr = malloc(sizeof(int*) * 10);
    float dist = 0;
    for(int i = 0; i < 10; i++) {
        arr[i] = malloc(sizeof(int));
        *arr[i] = i;
        if(i%2==0)
            dist = 1.14;
        else
            dist = 1.14 * i + 0.5;
        heap_push(heap, arr[i], dist);
    }

    heap_print(heap, print_int);

    free(arr);
    heap_destroy(heap);
    return 0;
}