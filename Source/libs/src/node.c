#include "../headers/node.h"
#include <stdlib.h>

Node *node_construct(unsigned short int value, Node *next){
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->next = next;
    return node;
}

unsigned short int node_get_value(Node *n){
    return n->value;
}

Node *node_get_next(Node *n){
    return n->next;
}

void *node_set_next(Node *n, Node *next){
    n->next = next;
}

void node_destroy(Node *n){
    free(n);
}

void node_destroy_recursive(Node* n){
    if (n==NULL){
        return;
    }
    node_destroy_recursive(n->next);
    node_destroy(n);
}