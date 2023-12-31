#include <stdio.h>
#include <stdlib.h>
#include "../headers/vertex.h"
#include "../headers/utils.h"

struct vertex{
    float x;
    float y;
    unsigned short int priority;
};

vertex* vertex_init(float x, float y){
    vertex* c = malloc(sizeof(vertex));
    c->x = x;
    c->y = y;
    return c;
}

void vertex_set_priority(vertex* c, unsigned short int priority){
    c->priority = priority;
}

unsigned short int vertex_get_priority(vertex* c){
    return c->priority;
}

float vertex_get_x(vertex* c){
    return c->x;
}

float vertex_get_y(vertex* c){
    return c->y;
}

void vertex_destroy_wrapper(void* c, ...){
    vertex_destroy((vertex*) c);
}

void vertex_destroy(vertex* c){
    free((vertex*) c);
}

int vertex_compare(void* c1, void* c2){
    vertex* c1_casted = (vertex*) c1;
    vertex* c2_casted = (vertex*) c2;
    if(c1_casted->x == c2_casted->x && c1_casted->y == c2_casted->y)
        return 0;
    return 1;
}

void vertex_print(vertex* v){
    printf("x: %f, y: %f\n", v->x, v->y);
}

float vertex_euclidean_distance(vertex* c1, vertex* c2){
    return euclidean_distance(c1->x, c1->y, c2->x, c2->y);
}