#include<stdlib.h>
#include<stdio.h>
#include "../headers/node.h"
#include "../headers/forward_list.h"

ForwardList *forward_list_construct(){
    ForwardList *frwd_list = (ForwardList *)malloc(sizeof(ForwardList));
    frwd_list->head= NULL;
    frwd_list->size = 0;
    frwd_list->city = 0;
    return frwd_list;
}

unsigned short int forward_list_get_city(ForwardList* l){
    return l->city;
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
    l->city = city;
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

Node* forward_list_get_head_node(ForwardList *l){
    return l->head;
}

unsigned short int forward_list_get_head_value(ForwardList *l){
    return node_get_value(l->head);
}
typedef int (*list_comp_fn)(const void*, const void*);
Node* forward_list_get_node(ForwardList *l, unsigned short int i){
    unsigned short int count = 0;
    unsigned short int len = forward_list_size(l);
    Node* reference = l->head;

    while(count < len){
        if(count == i){
            l->head = reference;
            return l->head;
        }
        l->head = node_get_next(l->head);
        count++;
    }
    return NULL;
}


unsigned short int forward_list_get(ForwardList *l, unsigned short int i){
    unsigned short int count = 0;
    unsigned short int val = 0;
    unsigned short int len = forward_list_size(l);
    Node* reference = l->head;

    while(count < len){
        if(count == i){
            val = node_get_value(l->head);
            l->head = reference;
            return val;
        }
        l->head = node_get_next(l->head);
        count++;
    }
    return val;
}

unsigned short int forward_list_pop_front(ForwardList *l){
    Node* reference = node_get_next(l->head);
    unsigned short int val = node_get_value(l->head);
    free(l->head);

    l->head = reference;
    l->size--;

    return val;
}

void forward_list_remove_node(ForwardList *l, Node* n){
    Node* reference = l->head;
    Node* prev = NULL;
    while(l->head != NULL){
        if(l->head == n){
            if(prev == NULL){
                l->head = node_get_next(l->head);
                free(prev);
                l->size--;
                free(n);
                return;
            }
            Node * prev_next = node_get_next(prev); 
            prev_next = node_get_next(l->head);
            free(l->head);
            l->head = reference;
            l->size--;
            free(n);
            return;
        }
        prev = l->head;
        l->head = node_get_next(l->head);
    }
    l->head = reference;
}

void forward_list_cat(ForwardList *l, ForwardList *m){
    Node* reference = l->head;
    while(l->head != NULL){
        l->head = node_get_next(l->head);
    }
    l->head = m->head;
    l->head = reference;
}

void forward_list_destroy(ForwardList *l){
    node_destroy_recursive(l->head);
    free(l);
}

unsigned short int forward_list_is_empty(ForwardList *l){
    if(l->head == NULL) return 1;
    return 0;
}