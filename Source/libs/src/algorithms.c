#include <stdio.h>
#include <stdlib.h>
#include "../headers/algorithms.h"
#include "../headers/union_find.h"
#include "../headers/vertex.h"
#include "../headers/utils.h"
#include "../headers/edge.h"


// ========================== | CONNECT NODES | ==========================

// 1) Pascal Complexity (size) Algorithm
int pascal_size(int n_memb){
    int sz = n_memb-1;
    return (sz*(sz+1))/2;
}

int _edge_cmp_(const void* a, const void* b){
    edge* e1 = *(edge**)a;
    edge* e2 = *(edge**)b;
    float d1 = edge_get_distance(e1);
    float d2 = edge_get_distance(e2);
    if(d1 > d2){
        return 1;
    }else if(d1 < d2){
        return -1;
    }else{
        return 0;
    }
}

edge** pascal_connections(vertex** nodes, int n_memb){
    float dist = 0;
    int position = 0;
    edge** edges = malloc(sizeof(edge*) * pascal_size(n_memb));
    for(int i = 0; i < n_memb; i++){
        for(int j = i + 1; j < n_memb; j++){
            dist = vertex_euclidean_distance(*(nodes + i), *(nodes + j));
            edges[position++] = edge_init(*(nodes + i), *(nodes + j), dist);
        }
    }
    edge_sort(edges, pascal_size(n_memb), _edge_cmp_);
    return edges;
}

// 2) I DONT KNOW


// ========================== | BUILD THE TREE | ==========================
union_find* tsp_build_tree(int n_memb, vertex** nodes, compare_fn vertex_compare_fn, destroy_fn vertex_destroy_fn){
    int priority = 0;
    union_find* uf = uf_init(n_memb, vertex_compare_fn, vertex_destroy_fn);

    // remove from here. this is just for testing. this data should be passed as parameter.
    vertex** points = nodes;
    points = malloc(sizeof(vertex*) * n_memb);
    for(int i=0; i<n_memb; i++){
        points[i] = vertex_init(rand() % 10, rand() % 10);
        uf_create_node(uf, points[i], priority);
        vertex_set_priority(points[i], priority);
        priority++;
    }
    // end

    edge** edge_arr = pascal_connections(points, n_memb);
    for(int i = 0; i < pascal_size(n_memb); i++){
        edge* node = edge_arr[i];
        vertex* node1 = edge_get_node1(node);
        vertex* node2 = edge_get_node2(node);
        tree_node* t1 = uf_find_node(uf, vertex_get_priority(node1));
        tree_node* t2 = uf_find_node(uf, vertex_get_priority(node2));
        uf_union(uf, t1, t2);
    }
    return uf;
}

