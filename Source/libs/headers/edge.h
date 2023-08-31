#ifndef _EDGE_
#define _EDGE_
#include "../headers/vertex.h"

typedef struct edge edge;

/**
 * @brief Initialize a edge object
 * 
 * @param node1 
 * @param node2 
 * @param distance 
 * @return edge* 
 * 
 * @note Complexity: O(1)
 */
edge* edge_init(vertex* node1, vertex* node2, float distance);

/**
 * @brief Get the node2 object
 * 
 * @param e 
 * @return vertex* 
 * 
 * @note Complexity: O(1)
 */
vertex* edge_get_node1(edge* e);

/**
 * @brief Get the node2 object
 * 
 * @param e 
 * @return vertex* 
 * 
 * @note Complexity: O(1)
 */
vertex* edge_get_node2(edge* e);

/**
 * @brief Get the distance object
 * 
 * @param e 
 * @return float 
 * 
 * @note Complexity: O(1)
 */
float edge_get_distance(edge* e);

/**
 * @brief Set the distance object
 * 
 * @param e 
 * @param distance 
 * 
 * @note Complexity: O(1)
 */
void edge_set_distance(edge* e, float distance);

/**
 * @brief Calculate the distance between two nodes.
 * 
 * @param e 
 * 
 * @note Complexity: O(1)
 */
float edge_calc_distance(edge* e);

/**
 * @brief Sort an array of edges.
 * 
 * @param edge_arr 
 * @param size 
 * @param compare 
 * 
 * @note Complexity: O(nlog(n))
 */
void edge_sort(edge** edge_arr, int size, int (*compare)(const void*, const void*));

/**
 * @brief Dealloc memory allocated for edge object.
 * 
 * @param e 
 * 
 * @note Complexity: O(1)
 */
void edge_destroy(edge* e);

#endif