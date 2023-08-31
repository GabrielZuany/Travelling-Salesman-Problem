#include <stdio.h>
#include <stdlib.h>
#include "../headers/vertex.h"
#include "../headers/edge.h"
#include "../headers/utils.h"

struct edge{
    vertex* node1;
    vertex* node2;
    float distance;
};

edge* edge_init(vertex* node1, vertex* node2, float distance){
    edge* e = malloc(sizeof(edge));
    e->node1 = node1;
    e->node2 = node2;
    e->distance = distance;
    return e;
}

void edge_set_distance(edge* e, float distance){
    e->distance = distance;
}

float edge_calc_distance(edge* e){
    e->distance = vertex_euclidean_distance(e->node1, e->node2);
    return e->distance;
}

vertex* edge_get_node1(edge* e){
    return e->node1;
}

vertex* edge_get_node2(edge* e){
    return e->node2;
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