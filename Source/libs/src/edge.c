#include <stdio.h>
#include <stdlib.h>
#include "../headers/vertex.h"
#include "../headers/edge.h"
#include "../headers/utils.h"

struct edge{
    int idx_node_1;
    int idx_node_2;
    float distance;
};

edge* edge_init(int node1, int node2, float distance){
    edge* e = malloc(sizeof(edge));
    e->idx_node_1 = node1;
    e->idx_node_2 = node2;
    e->distance = distance;
    return e;
}

void edge_set_distance(edge* e, float distance){
    e->distance = distance;
}

int edge_get_node1_idx(edge* e){
    return e->idx_node_1;
}

int edge_get_node2_idx(edge* e){
    return e->idx_node_2;
}

float edge_get_distance(edge* e){
    return e->distance;
}

void edge_sort(edge** edge_arr, int size, int (*compare)(const void*, const void*)){
    qsort(edge_arr, size, sizeof(edge*), compare);
}

void edge_destroy(edge* e){
    free(e);
}