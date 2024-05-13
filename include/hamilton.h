#ifndef HAMILTON_H
#define HAMILTON_H


#include "structs_unions_defines.h"

/**
 * @brief Determines if given graph contains a Hamiltionian cycle.
 * 
 * @param adjM adjacency matrix
 * @param n number of vertices
 * @param start starting vertex
 * @param placeholder variable for holding a pointer to found path
 * @return SUCCESS on finding a cycle, FAILURE on not, MEMORY_FAILURE on memory allocation error
 */
status_t HamiltonianCycleA(char** adjM, int n, int start, int** placeholder);

/**
 * @brief Determines if given graph contains a Hamiltionian cycle.
 * 
 * @param grM graph matrix
 * @param n number of vertices
 * @param start starting vertex
 * @param placeholder variable for holding a pointer to found path
 * @return SUCCESS on finding a cycle, FAILURE on not, MEMORY_FAILURE on memory allocation error 
 */
status_t HamiltonianCycleM(int** grM, int n, int start, int** placeholder);


#endif