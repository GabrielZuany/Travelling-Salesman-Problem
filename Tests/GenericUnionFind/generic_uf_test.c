#include <stdio.h>
#include <stdlib.h>
#include "../../Source/libs/headers/union_find.h"

typedef struct Cell{
    int x;
    int y;
    int* unused_arr;
}Cell;

int cmp(void*a, void*b){
    Cell* c1 = (Cell*)a;
    Cell* c2 = (Cell*)b;
    return c1->x == c2->x && c1->y == c2->y;
}

void destroy(void* a, ...){
    free(((Cell*)a)->unused_arr);
    free(a);
}

int main(){
    union_find* uf = uf_init(10, cmp, destroy);
    int size = 10;
    Cell* cells[size];

    for(int i = 0; i < size; i++){
        cells[i] = malloc(sizeof(Cell));
        cells[i]->unused_arr = malloc(sizeof(int) * 10);
        cells[i]->x = i;
        cells[i]->y = i;
    }
    tree_node* nodes[size];
    for(int i = 0; i < size; i++){
        nodes[i] = uf_create_node(uf, cells[i], i);
    }

    uf_union(uf, nodes[4], nodes[3]);
    uf_union(uf, nodes[3], nodes[8]);
    uf_union(uf, nodes[6], nodes[5]);
    uf_union(uf, nodes[9], nodes[4]);
    uf_union(uf, nodes[2], nodes[1]);
    uf_union(uf, nodes[5], nodes[0]);
    uf_union(uf, nodes[7], nodes[2]);
    uf_union(uf, nodes[6], nodes[1]);
    uf_union(uf, nodes[7], nodes[3]);

    if(uf_is_connected(uf, nodes[0], nodes[3])){
        printf("CONNECTED\n");
    }else{
        printf("NOT CONNECTED\n");
    }

    _d_uf_print_(uf); // _DEV_
    
    uf_destroy(uf);
    return 0;
}