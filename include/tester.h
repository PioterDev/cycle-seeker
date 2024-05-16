#ifndef TESTER_H
#define TESTER_H


#include <windows.h>
/**
 * @brief Tests finding a cycle/circuit in a graph.
 * 
 * @param algorithm 'e' - finding Eulerian circuit, 'h' - finding Hamiltonian cycle
 * @param adjacencyMatrix 
 * @param graphMatrix 
 * @param vertices number of vertices
 * @return time taken to sort with accuracy of 1/QueryPerformanceFrequency(&freq)
 */
long long test(char algorithm, char** adjacencyMatrix, int** graphMatrix, int vertices);

DWORD WINAPI testThreaded(void* params);


#endif