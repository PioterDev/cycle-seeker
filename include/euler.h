#ifndef EULER_H
#define EULER_H


#include "structs_unions_defines.h"

/**
 * @brief Determines if a graph has an Eulerian circuit.
 * 
 * @param adjM adjacency matrix
 * @param n number of vertices
 * @param m number of edges
 * @param start starting vertex
 * @param placeholder variable for holding a pointer to found path
 * @return SUCCESS on finding a circuit, FAILURE on not, MEMORY_FAILURE on memory allocation error
 */
status_t EulerianCircuitA(char** adjM, int n, int m, int start, int** placeholder);

status_t EulerianCircuitM(int** grM, int n, int m, int start, int** placeholder);

#endif