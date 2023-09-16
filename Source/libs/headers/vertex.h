#ifndef _vertex_
#define _vertex_

typedef struct vertex vertex;

/**
 * @brief Create a vertex 'object'
 * 
 * @param x 
 * @param y 
 * @return vertex* 
 * 
 * @note Complexity: O(1)
 */
vertex* vertex_init(float x, float y);

/**
 * @brief Get the x coordinate
 * 
 * @param c 
 * @return float 
 * 
 * @note Complexity: O(1)
 */
float vertex_get_x(vertex* c);

/**
 * @brief Set the priority
 * 
 * @param c 
 * @param priority 
 * 
 * @note Complexity: O(1)
 */
void vertex_set_priority(vertex* c, int priority);

/**
 * @brief Get the priority
 * 
 * @param c 
 * @return int 
 * 
 * @note Complexity: O(1)
 */
int vertex_get_priority(vertex* c);

/**
 * @brief Get the y coordinate
 * 
 * @param c 
 * @return float 
 * 
 * @note Complexity: O(1)
 */
float vertex_get_y(vertex* c);

/**
 * @brief Destroy the vertex 'object'
 * 
 * @param c 
 * 
 * @note Complexity: O(1)
 */
void vertex_destroy(vertex* c);

/**
 * @brief 
 * 
 * @param c 
 * @param ... 
 */
void vertex_destroy_wrapper(void* c, ...);

/**
 * @brief Compare two vertex
 * 
 * @param c1 
 * @param c2 
 * @return int 
 * 
 * @note Complexity: O(1)
 */
int vertex_compare(void* c1, void* c2);

/**
 * @brief Calculate the euclidean distance between two vertex
 * 
 * @param c1 
 * @param c2 
 * @return float 
 * 
 * @note Complexity: O(1)
 */
float vertex_euclidean_distance(vertex* c1, vertex* c2);

#endif