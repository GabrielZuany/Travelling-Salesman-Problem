#include "../headers/utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float euclidean_distance(float x1, float y1, float x2, float y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
} 