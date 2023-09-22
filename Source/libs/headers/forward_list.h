
#ifndef _FORWARD_forward_list_H_
#define _FORWARD_forward_list_H_

#include "node.h"

typedef struct ForwardList ForwardList;

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
 * @brief Returns the id of the linked list.
 * 
 * @param l
 * Pointer to the linked list.
 * @return int
 * Id of the linked list.
 * 
 * @note Complexity: O(1)
 */
unsigned short int forward_list_get_id(ForwardList* l);

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
 * @brief Destroy the Linked List:: Linked List object
 *  Frees the memory allocated for the linked list.
 * @param l
 * Pointer to the linked list.
 * 
 * @note Complexity: O(n)
 */
void forward_list_remove_node(ForwardList *l, Node* n);

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
void forward_list_push_front(unsigned short int id, ForwardList *l, unsigned short int data);

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
 * @brief Returns the data stored in the node at the given index.
 * @param l
 * Pointer to the linked list.
 * @param i
 * Index of the node.
 * @return int
 * Data stored in the node at the given index.
 *
 * @note Complexity: O(n)
 */
unsigned short int forward_list_get(ForwardList *l, unsigned short int i);

/**
 * @brief Returns a pointer to the node at the given index.
 * @param l
 * Pointer to the linked list.
 * @param i
 * Index of the node.
 * @return Node*
 * Pointer to the node at the given index.
 *
 * @note Complexity: O(n)
 */
Node* forward_list_get_node(ForwardList *l, unsigned short int i);

/**
 * @brief Returns a pointer to the first node of the linked list.
 * @param l
 * Pointer to the linked list.
 * @return Node*
 * Pointer to the first node of the linked list.
 *
 * @note Complexity: O(1)
 */
Node* forward_list_get_head_node(ForwardList *l);

/**
 * @brief Returns a pointer to the data stored in the first node of the linked list.
 * @param l
 * Pointer to the linked list.
 * @return int
 * Pointer to the data stored in the first node of the linked list.
 *
 * @note Complexity: O(1)
 */
unsigned short int forward_list_get_head_value(ForwardList *l);

/**
 * @brief Remove the first node of the linked list and returns its data.
 * @param l
 * Pointer to the linked list.
 * @return int
 * Pointer to the data stored in the first node of the linked list that was removed.
 *
 * @note Complexity: O(1)
 */
unsigned short int forward_list_pop_front(ForwardList *l);

/**
 * @brief Adds all nodes from the given list to the end of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param m
 * Pointer to the linked list to be added to the end of the linked list.
 * 
 * @note Complexity: O(n)
 */
void forward_list_cat(ForwardList *l, ForwardList *m);

/**
 * @brief Destroys the linked list.
 *  Frees the memory allocated for the linked list and all its nodes.
 * @param l
 * Pointer to the linked list.
 *
 * @note Complexity: O(n)
 */
void forward_list_destroy(ForwardList *l);

/**
 * @brief Returns 1 if the linked list is empty, 0 otherwise.
 * @param l
 * Pointer to the linked list.
 * @return int
 * 1 if the linked list is empty, 0 otherwise.
 *
 * @note Complexity: O(1)
 */
unsigned short int forward_list_is_empty(ForwardList *l);

#endif