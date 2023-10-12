
#ifndef _FORWARD_forward_list_H_
#define _FORWARD_forward_list_H_

#include "node.h"

typedef struct
{
    Node *head;
    unsigned short int size;
}ForwardList;

/**
 * @brief Construct a new Linked List:: Linked List object
 *  Allocates memory for a new linked list and returns a pointer to it.
 * @return ForwardList*
 * Pointer to the newly allocated linked list.
 * @note
 * The caller is responsible for freeing the memory allocated for the linked list using forward_list_destroy().
 *
 * @note Complexity: O(1)   
 */
ForwardList *forward_list_construct();

/**
 * @brief Returns the size of the linked list.
 *  Returns the number of nodes in the linked list.
 * @param l
 * Pointer to the linked list.
 * @return int
 * Number of nodes in the linked list.
 * 
 * @note Complexity: O(1)
 */
unsigned short int forward_list_size(ForwardList *l);

/**
 * @brief Pushes a new node to the front of the linked list.
 *  Allocates memory for a new node and inserts it at the front of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param data
 * Pointer to the data to be stored in the new node.
 *
 * @note Complexity: O(1)
 */
void forward_list_push_front(unsigned short int city, ForwardList *l, unsigned short int data);

/**
 * @brief Prunsigned short int the elements of the linked list.
 *  Prunsigned short int the elements of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param print_fn
 * Pointer to the function to prunsigned short int unsigned short int values.
 *
 * @note Complexity: O(n)
 */
void forward_list_print(ForwardList *l, void (*print_fn)(int));

/**
 * @brief Destroys the linked list.
 *  Frees the memory allocated for the linked list and all its nodes.
 * @param l
 * Pointer to the linked list.
 *
 * @note Complexity: O(n)
 */
void forward_list_destroy(ForwardList *l);

#endif