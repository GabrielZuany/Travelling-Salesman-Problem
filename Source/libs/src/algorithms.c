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
            edges[position++] = edge_init(i, j, dist);
        }
    }
    edge_sort(edges, pascal_size(n_memb), _edge_cmp_);
    return edges;
}

// 2) I DONT KNOW


// ========================== | BUILD THE TREE | ==========================
union_find* tsp_build_tree(int n_memb, vertex** points, compare_fn vertex_compare, destroy_fn vertex_destroy){
    
    int priority = 0;
    union_find* uf = uf_init(n_memb, vertex_compare, vertex_destroy);
    for(int i = 0; i<n_memb; i++){
        uf_create_node(uf, points[i], priority);
        vertex_set_priority(points[i], priority);
        priority++;
    }

    edge** edge_arr = pascal_connections(points, n_memb);
    for(int i = 0; i < pascal_size(n_memb); i++){
        edge* edge1 = edge_arr[i];
        vertex* n1 = points[edge_get_node1_idx(edge1)];
        vertex* n2 = points[edge_get_node2_idx(edge1)];
        tree_node* t1 = uf_find_node(uf, vertex_get_priority(n1));
        tree_node* t2 = uf_find_node(uf, vertex_get_priority(n2));
        uf_union(uf, t1, t2);
    }
    return uf;
}

