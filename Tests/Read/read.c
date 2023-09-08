#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Source/libs/headers/union_find.h"
#include "../../Source/libs/headers/vertex.h"
#include "../../Source/libs/headers/utils.h"
#include "../../Source/libs/headers/edge.h"
#include "../../Source/libs/headers/tsp.h"

int main(int argc, char** argv){
    vertex** points = tsp_read(argv[1]);
    union_find* uf = tsp_build_tree(points, vertex_compare, vertex_destroy);

    uf_destroy(uf);
    free(points);
    return 0;
}