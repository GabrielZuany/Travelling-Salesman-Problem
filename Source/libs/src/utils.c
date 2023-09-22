#include "../headers/utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float euclidean_distance(float x1, float y1, float x2, float y2){
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
} 