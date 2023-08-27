#include <stdio.h>
#include <stdlib.h>
#include "../Source/libs/headers/union_find.h"

int cmp(void*a, void*b){
    return *(int*)a == *(int*)b;
}

void destroy(void* a, ...){
    free(a);
}

int main(){

    union_find* uf = uf_init(10, cmp, destroy);
    int* a = malloc(sizeof(int));
    *a = 1;
    int* b = malloc(sizeof(int));
    *b = 2;
    int* c = calloc(sizeof(int), 1);

    tree_node* n1 = uf_create_node(uf, a, 1);
    tree_node* n2 = uf_create_node(uf, b, 2);
    tree_node* n3 = uf_create_node(uf, c, 0); 

    uf_union(uf, n1, n2);
    
    if(uf_is_connected(uf, n1, n3)){
        printf("CONNECTED");
    }else{
        printf("NOT CONNECTED");
    }
    
    uf_destroy(uf);
    return 0;
}