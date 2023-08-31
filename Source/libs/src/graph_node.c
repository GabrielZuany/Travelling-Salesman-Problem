#include <stdio.h>
#include <stdlib.h>
#include "../headers/graph_node.h"
#include "../headers/utils.h"

struct graph_node
{
    float x;
    float y;
    int priority;
};

graph_node* graph_node_init(float x, float y){
    graph_node* c = malloc(sizeof(graph_node));
    c->x = x;
    c->y = y;
    return c;
}

void graph_node_set_priority(graph_node* c, int priority){
    c->priority = priority;
}

int graph_node_get_priority(graph_node* c){
    return c->priority;
}

float graph_node_get_x(graph_node* c){
    return c->x;
}

float graph_node_get_y(graph_node* c){
    return c->y;
}

void graph_node_destroy(graph_node* c){
    free(c);
}

int graph_node_compare(void* c1, void* c2){
    graph_node* c1_casted = (graph_node*) c1;
    graph_node* c2_casted = (graph_node*) c2;
    if(c1_casted->x == c2_casted->x && c1_casted->y == c2_casted->y)
        return 0;
    return 1;
}

float graph_node_euclidean_distance(graph_node* c1, graph_node* c2){
    return euclidean_distance(c1->x, c1->y, c2->x, c2->y);
}