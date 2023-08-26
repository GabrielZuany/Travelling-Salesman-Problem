#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "union_find.h"

struct tree_node{
    void* data;
    int _priority;
};

struct union_find{
    tree_node* tree_nodes;
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
    uf->tree_nodes = malloc(sizeof(tree_node) * size);
    uf->size_trees_arr = malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++){
        uf->tree_nodes[i].data = NULL;
        uf->tree_nodes[i]._priority = i;
        uf->size_trees_arr[i] = 1;
    }
    return uf;
}

void uf_destroy(union_find* uf){
    for(int i = 0; i < uf->size; i++){
        if(uf->tree_nodes[i].data != NULL){
            uf->destroy(uf->tree_nodes[i].data);
        }
    }
    free(uf->tree_nodes);
    free(uf->size_trees_arr);
    free(uf);
}

int _root_index(union_find* uf, void* node){
    int i = 0;
    while (!(uf->compare(uf->tree_nodes[i].data, node))) // while not reach the root
    {
        uf->tree_nodes[i] = uf->tree_nodes[uf->tree_nodes[i]._priority]; // copy?
        i = uf->tree_nodes[i]._priority;
    }
    return i;
}

void* uf_find(union_find* uf, void* node){

}

void uf_union(union_find* uf, void* node1, void* node2){
    tree_node n1 = uf->tree_nodes[_root_index(uf, node1)];
    tree_node n2 = uf->tree_nodes[_root_index(uf, node2)];
    
}

bool uf_is_connected(union_find* uf, void* node1, void* node2){

}
