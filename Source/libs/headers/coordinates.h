#ifndef _COORDINATES_
#define _COORDINATES_

typedef struct coordinates coordinates;

/**
 * @brief Create a coordinates 'object'
 * 
 * @param x 
 * @param y 
 * @return coordinates* 
 * 
 * @note Complexity: O(1)
 */
coordinates* coordinates_init(float x, float y);

/**
 * @brief Get the x coordinate
 * 
 * @param c 
 * @return float 
 * 
 * @note Complexity: O(1)
 */
float coordinates_get_x(coordinates* c);

/**
 * @brief Get the y coordinate
 * 
 * @param c 
 * @return float 
 * 
 * @note Complexity: O(1)
 */
float coordinates_get_y(coordinates* c);

/**
 * @brief Destroy the coordinates 'object'
 * 
 * @param c 
 * 
 * @note Complexity: O(1)
 */
void coordinates_destroy(coordinates* c);

/**
 * @brief Compare two coordinates
 * 
 * @param c1 
 * @param c2 
 * @return int 
 * 
 * @note Complexity: O(1)
 */
int coordinates_compare(void* c1, void* c2);

/**
 * @brief Calculate the euclidean distance between two coordinates
 * 
 * @param c1 
 * @param c2 
 * @return float 
 * 
 * @note Complexity: O(1)
 */
float coordinates_euclidean_distance(coordinates* c1, coordinates* c2);

#endif