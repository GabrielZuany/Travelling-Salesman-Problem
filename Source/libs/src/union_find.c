#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../headers/union_find.h"

struct tree_node{
    void* data;
    unsigned short int _priority;
};

struct union_find{
    tree_node* tree_nodes;
    unsigned short int* size_trees_arr;
    unsigned short int size;
    compare_fn compare;
    destroy_fn destroy;
};

union_find* uf_init(unsigned short int size, compare_fn cmp, destroy_fn destroy){
    union_find* uf = malloc(sizeof(union_find));
    uf->compare = cmp;
    uf->destroy = destroy;
    uf->size = size;
    uf->tree_nodes = malloc(sizeof(tree_node) * size);
    uf->size_trees_arr = malloc(sizeof(unsigned short int) * size);
    for(unsigned short int i = 0; i < size; i++){
        uf->tree_nodes[i].data = NULL;
        uf->tree_nodes[i]._priority = (unsigned short int)i;
        uf->size_trees_arr[i] = 1;
    }
    return uf;
}

void uf_destroy(union_find* uf){
    for(unsigned short int i = 0; i < uf->size; i++){
        if(uf->tree_nodes[i].data != NULL){
            uf->destroy(uf->tree_nodes[i].data);
        }  
    }
    free(uf->tree_nodes);
    free(uf->size_trees_arr);
    free(uf);
}

unsigned short int _root_index(union_find* uf, unsigned short int i){
    while (!(uf->tree_nodes[i]._priority == i)) // while not reach the root
    {
        uf->tree_nodes[i]._priority = uf->tree_nodes[uf->tree_nodes[i]._priority]._priority;
        i = uf->tree_nodes[i]._priority;
    }
    return i;
}

unsigned short int tree_node_get_priority(tree_node* node){
    return node->_priority;
}

void* uf_find_root(union_find* uf, tree_node* node){
    return uf->tree_nodes[_root_index(uf, node->_priority)].data;
}

tree_node* uf_find_node(union_find* uf, unsigned short int priority){
    return &(uf->tree_nodes[priority]);
}

boolean _tree_node_is_equal(union_find* uf, tree_node n1, tree_node n2){
    if (n1._priority == n2._priority && uf->compare(n1.data, n2.data)){
        return True;
    }return False;
}

tree_node* uf_create_node(union_find* uf, void* new_node, unsigned short int priority){
    uf->tree_nodes[priority].data = new_node;
    uf->tree_nodes[priority]._priority = priority;
    tree_node* tn = &(uf->tree_nodes[priority]);
    return tn;
}

boolean uf_union(union_find* uf, tree_node* node1, tree_node* node2){
    unsigned short int n1_idx = _root_index(uf, node1->_priority);
    unsigned short int n2_idx = _root_index(uf, node2->_priority);
    tree_node n1 = uf->tree_nodes[n1_idx];
    tree_node n2 = uf->tree_nodes[n2_idx];
    if(_tree_node_is_equal(uf, n1, n2) == True || n1_idx == n2_idx){
        return False;
    }
    if(uf->size_trees_arr[n1_idx] < uf->size_trees_arr[n2_idx]){
        uf->tree_nodes[n1_idx]._priority = uf->tree_nodes[n2_idx]._priority;
        uf->size_trees_arr[n2_idx] += uf->size_trees_arr[n1_idx];
    }else{
        uf->tree_nodes[n2_idx]._priority = uf->tree_nodes[n1_idx]._priority;
        uf->size_trees_arr[n1_idx] += uf->size_trees_arr[n2_idx];
    }
    return True;
}

boolean uf_is_connected(union_find* uf, tree_node* node1, tree_node* node2){
    unsigned short int n1_idx = _root_index(uf, node1->_priority);
    unsigned short int n2_idx = _root_index(uf, node2->_priority);
    tree_node n1 = uf->tree_nodes[n1_idx];
    tree_node n2 = uf->tree_nodes[n2_idx];
    if(n1._priority == n2._priority){
        return True;
    }return False;
}
