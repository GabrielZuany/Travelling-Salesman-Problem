#include <stdio.h>
#include <stdlib.h>
#include "../headers/coordinates.h"
#include "../headers/utils.h"

struct coordinates
{
    float x;
    float y;
};

coordinates* coordinates_init(float x, float y){
    coordinates* c = malloc(sizeof(coordinates));
    c->x = x;
    c->y = y;
    return c;
}

float coordinates_get_x(coordinates* c){
    return c->x;
}

float coordinates_get_y(coordinates* c){
    return c->y;
}

void coordinates_destroy(coordinates* c){
    free(c);
}

float coordinates_euclidean_distance(coordinates* c1, coordinates* c2){
    return euclidean_distance(c1->x, c1->y, c2->x, c2->y);
}