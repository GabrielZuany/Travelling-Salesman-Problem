#include <stdio.h>
#include <stdlib.h>
#include "../headers/connection.h"
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
