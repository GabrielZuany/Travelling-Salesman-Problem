#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../headers/union_find.h"

struct union_find{
    void** nodes;
    int* size_trees_arr;
    int size;
    uf_compare_fn compare;
    uf_destroy_fn destroy;
};

union_find* uf_init(int size, uf_compare_fn cmp, uf_destroy_fn destroy){
    union_find* uf = malloc(sizeof(union_find));
    uf->compare = cmp;
    uf->destroy = destroy;
    uf->size = size;
    uf->nodes = malloc(sizeof(void*) * size);
    uf->size_trees_arr = malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++){
        uf->nodes[i] = NULL;
        uf->size_trees_arr[i] = 1;
    }
    return uf;
}

void uf_destroy(union_find* uf){
    for(int i = 0; i < uf->size; i++){
        if(uf->nodes[i] != NULL){
            uf->destroy(uf->nodes[i]);
        }
    }
    free(uf->nodes);
    free(uf->size_trees_arr);
    free(uf);
}



