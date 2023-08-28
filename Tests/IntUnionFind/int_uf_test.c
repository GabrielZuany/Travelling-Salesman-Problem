#include <stdio.h>
#include <stdlib.h>
#include "../../Source/libs/headers/union_find.h"

int cmp_int(void*a, void*b){
    return *(int*)a == *(int*)b;
}

void destroy_int(void* a, ...){
    free(a);
}

void print_int(void* a){
    printf("%d ", *(int*)a);
}

int main(){
    union_find* uf = uf_init(10, cmp_int, destroy_int);
    tree_node** nodes = _d_uf_fill_int_(uf); // _DEV_

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

    tree_node* node = uf_find_node(uf, 1);
    printf("Node data: ");
    _d_print_node_(node, print_int); // _DEV_

    int* root = uf_find_root(uf, nodes[1]);
    printf(" => Root: %d\n", *root);
    
    uf_destroy(uf);
    return 0;
}