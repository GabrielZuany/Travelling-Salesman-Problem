#include<stdlib.h>
#include<stdio.h>
#include "../headers/node.h"
#include "../headers/forward_list.h"

ForwardList *forward_list_construct(){
    ForwardList *frwd_list = (ForwardList *)malloc(sizeof(ForwardList));
    frwd_list->head= NULL;
    frwd_list->size = 0;
    return frwd_list;
}

unsigned short int forward_list_size(ForwardList *l){
    if(l == NULL)
        return 0;
    return l->size;
}

void forward_list_push_front(unsigned short int city, ForwardList *l, unsigned short int data){
    Node * N = node_construct(data, l->head);
    l->head = N;
    l->size++;
}

void forward_list_print(ForwardList *l, void (*print_fn)(int)){
    Node* reference = l->head;

    printf("[");
    while(l->head != NULL){
        print_fn(node_get_value(l->head));
        if(node_get_next(l->head) != NULL) 
            printf(", "); 

        l->head = node_get_next(l->head);
    }
    printf("]");
    l->head = reference;
}

unsigned short int forward_list_pop_front(ForwardList *l){
    Node* reference = node_get_next(l->head);
    unsigned short int val = node_get_value(l->head);
    free(l->head);

    l->head = reference;
    l->size--;

    return val;
}

void forward_list_destroy(ForwardList *l){
    node_destroy_recursive(l->head);
    free(l);
}
