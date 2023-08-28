#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../headers/union_find.h"

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

int _root_index(union_find* uf, int i){
    while (!(uf->tree_nodes[i]._priority == i)) // while not reach the root
    {
        uf->tree_nodes[i]._priority = uf->tree_nodes[uf->tree_nodes[i]._priority]._priority;
        i = uf->tree_nodes[i]._priority;
    }
    return i;
}

void* uf_find_root(union_find* uf, tree_node* node){
    return uf->tree_nodes[_root_index(uf, node->_priority)].data;
}

tree_node* uf_find_node(union_find* uf, int priority){
    return &(uf->tree_nodes[priority]);
}

int _tree_node_is_equal(union_find* uf, tree_node n1, tree_node n2){
    return (n1._priority == n2._priority && uf->compare(n1.data, n2.data));
}

tree_node* uf_create_node(union_find* uf, void* new_node, int priority){
    uf->tree_nodes[priority].data = new_node;
    uf->tree_nodes[priority]._priority = priority;
    tree_node* tn = &(uf->tree_nodes[priority]);
    return tn;
}

void uf_union(union_find* uf, tree_node* node1, tree_node* node2){
    int n1_idx = _root_index(uf, node1->_priority);
    int n2_idx = _root_index(uf, node2->_priority);
    tree_node n1 = uf->tree_nodes[n1_idx];
    tree_node n2 = uf->tree_nodes[n2_idx];
    if(_tree_node_is_equal(uf, n1, n2)){
        return;
    }
    if(uf->size_trees_arr[n1_idx] < uf->size_trees_arr[n2_idx]){
        uf->tree_nodes[n1_idx]._priority = uf->tree_nodes[n2_idx]._priority;
        uf->size_trees_arr[n2_idx] += uf->size_trees_arr[n1_idx];
    }else{
        uf->tree_nodes[n2_idx]._priority = uf->tree_nodes[n1_idx]._priority;
        uf->size_trees_arr[n1_idx] += uf->size_trees_arr[n2_idx];
    }
}

int uf_is_connected(union_find* uf, tree_node* node1, tree_node* node2){
    int n1_idx = _root_index(uf, node1->_priority);
    int n2_idx = _root_index(uf, node2->_priority);
    tree_node n1 = uf->tree_nodes[n1_idx];
    tree_node n2 = uf->tree_nodes[n2_idx];
    return n1._priority == n2._priority;
}

#ifdef _DEV_
void _d_uf_print_(union_find* uf){
    for(int i = 0; i < uf->size; i++){
        printf("%d ", i);
    }
    printf(" => ARR IDX\n");
    for(int i = 0; i < uf->size; i++){
        printf("| ");
    }
    printf("\n");
    for(int i = 0; i < uf->size; i++){
        printf("v ");
    }
    printf("\n");
    for(int i = 0; i < uf->size; i++){
        printf("%d ", uf->tree_nodes[i]._priority);
    }
    printf(" => PRIORITY\n");
}

tree_node** _d_uf_fill_int_(union_find* uf){
    int size = uf->size;
    int** arr = malloc(sizeof(int*) * size);
    for(int i = 0; i < size; i++){
        arr[i] = malloc(sizeof(int));
        *arr[i] = i;
    }

    tree_node** nodes = malloc(sizeof(tree_node*) * size);
    for(int i = 0; i < size; i++){
        nodes[i] = uf_create_node(uf, arr[i], i);
    }
    return nodes;
}

//function pointer
void _d_print_node_(tree_node* n, void (*print_fn)(void*))
{
    print_fn(n->data);
    printf(" => Priority: %d", n->_priority);
}
#endif