#ifndef RNG_H
#define RNG_H


/**
 * @brief Generates a sequence of integers from 1 to n.
 * 
 * @param n
 * @return sequence, NULL on allocation error 
 */
int* sequence(int n);

/**
 * @brief Generates a (hopefully) random permutation of an input array.
 * 
 * @param arr array
 * @param n length of the array
 * @return permutation of the array, NULL on allocation error
 */
int* permute(int* arr, int n);

/**
 * @brief Generates a random undirected graph with a Hamiltonian cycle.
 * 
 * @param matrix adjacency matrix to store edges
 * @param n number of vertices
 * @param percentFull % of n(n - 1)/2 possible edges will be generated
 * @return SUCCESS on success, MEMORY_FAILURE on allocation error
 */
status_t genHamiltonianU(char** matrix, int n, unsigned int percentFull, int* P);

/**
 * @brief Generates a random directed graph with a Hamiltonian cycle.
 * 
 * @param matrix adjacency matrix to store edges
 * @param n number of vertices
 * @param percentFull % of n(n - 1) possible edges will be generated
 * @return SUCCESS on success, MEMORY_FAILURE on allocation error
 */
status_t genHamiltonianD(char** matrix, int n, unsigned int percentFull, int* P);

/**
 * @brief Generates a random undirected graph without (hopefully) a Hamiltonian cycle.
 * 
 * @param matrix adjacency matrix to store edges
 * @param n number of vertices
 * @param percentFull % of n(n - 1)/2 possible edges will be generated
 * @return SUCCESS on success, MEMORY_FAILURE on allocation error
 */
status_t genNonHamiltonianU(char** matrix, int n, unsigned int percentFull);

/**
 * @brief Generates a random directed graph without (hopefully) a Hamiltonian cycle.
 * 
 * @param matrix adjacency matrix to store edges
 * @param n number of vertices
 * @param percentFull % of n(n - 1) possible edges will be generated
 * @return SUCCESS on success, MEMORY_FAILURE on allocation error
 */
status_t genNonHamiltonianD(char** matrix, int n, unsigned int percentFull);

/**
 * @brief Generates a random undirected graph with an Eulerian circuit.
 * 
 * @param matrix adjacency matrix to store edges
 * @param n number of vertices
 * @param percentFull % of n(n - 1)/2 possible edges will be generated
 * @param edges variable to store how many edges were generated
 * @return SUCCESS on success, MEMORY_FAILURE on allocation error
 */
status_t genEulerianU(char** matrix, int n, unsigned int percentFull, int* edges);

status_t genEulerianD(char** matrix, int n, unsigned int percentFull, int* edges);

status_t genNonEulerianU(char** matrix, int n, unsigned int percentFull, int* edges);


#endif