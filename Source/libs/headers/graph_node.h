#ifndef _graph_node_
#define _graph_node_

typedef struct graph_node graph_node;

/**
 * @brief Create a graph_node 'object'
 * 
 * @param x 
 * @param y 
 * @return graph_node* 
 * 
 * @note Complexity: O(1)
 */
graph_node* graph_node_init(float x, float y);

/**
 * @brief Get the x coordinate
 * 
 * @param c 
 * @return float 
 * 
 * @note Complexity: O(1)
 */
float graph_node_get_x(graph_node* c);

/**
 * @brief Set the priority
 * 
 * @param c 
 * @param priority 
 * 
 * @note Complexity: O(1)
 */
void graph_node_set_priority(graph_node* c, int priority);

/**
 * @brief Get the priority
 * 
 * @param c 
 * @return int 
 * 
 * @note Complexity: O(1)
 */
int graph_node_get_priority(graph_node* c);

/**
 * @brief Get the y coordinate
 * 
 * @param c 
 * @return float 
 * 
 * @note Complexity: O(1)
 */
float graph_node_get_y(graph_node* c);

/**
 * @brief Destroy the graph_node 'object'
 * 
 * @param c 
 * 
 * @note Complexity: O(1)
 */
void graph_node_destroy(graph_node* c);

/**
 * @brief Compare two graph_node
 * 
 * @param c1 
 * @param c2 
 * @return int 
 * 
 * @note Complexity: O(1)
 */
int graph_node_compare(void* c1, void* c2);

/**
 * @brief Calculate the euclidean distance between two graph_node
 * 
 * @param c1 
 * @param c2 
 * @return float 
 * 
 * @note Complexity: O(1)
 */
float graph_node_euclidean_distance(graph_node* c1, graph_node* c2);

#endif