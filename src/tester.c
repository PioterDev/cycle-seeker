#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "euler.h"
#include "hamilton.h"
#include "rng.h"
#include "structs_unions_defines.h"
#include "utils.h"

long long test(char algorithm, char** adjacencyMatrix, int** graphMatrix, int vertices, int edges, FILE* debug) {
    LARGE_INTEGER start, end;
    long long result;
    switch(algorithm) {
        case 'e': { //euler
            if(adjacencyMatrix != NULL) {
                int* circuit = NULL;
                QueryPerformanceCounter(&start);
                status_t eulerian = EulerianCircuitA(adjacencyMatrix, vertices, edges, 1, &circuit);
                QueryPerformanceCounter(&end);
                switch(eulerian) {
                    case MEMORY_FAILURE:
                        result = -1;
                        break;
                    case FAILURE:
                        result = end.QuadPart - start.QuadPart;
                        break;
                    case SUCCESS:
                        if(circuit != NULL)free(circuit);
                        result = -2;
                        break;
                }
            }
            else if(graphMatrix != NULL) {
                int* circuit = NULL;
                QueryPerformanceCounter(&start);
                status_t eulerian = EulerianCircuitM(graphMatrix, vertices, edges, 1, &circuit);
                QueryPerformanceCounter(&end);
                switch(eulerian) {
                    case MEMORY_FAILURE:
                        result = -1;
                        break;
                    case FAILURE:
                        result = end.QuadPart - start.QuadPart;
                        break;
                    case SUCCESS:
                        if(circuit != NULL)free(circuit);
                        result = -2;
                        break;
                }
            }
            break;
        }
        case 'h': { //hamilton
            if(adjacencyMatrix != NULL) {
                int* cycle = NULL;
                QueryPerformanceCounter(&start);
                status_t hamilton = HamiltonianCycleA(adjacencyMatrix, vertices, 1, &cycle);
                QueryPerformanceCounter(&end);
                switch(hamilton) {
                    case MEMORY_FAILURE:
                        result = -1;
                        break;
                    case FAILURE:
                        result = -2;
                        break;
                    case SUCCESS:
                        if(cycle != NULL)free(cycle);
                        result = end.QuadPart - start.QuadPart;
                        break;
                }
            }
            else if(graphMatrix != NULL) {
                int* cycle = NULL;
                QueryPerformanceCounter(&start);
                status_t hamilton = HamiltonianCycleM(graphMatrix, vertices, 1, &cycle, debug);
                QueryPerformanceCounter(&end);
                switch(hamilton) {
                    case MEMORY_FAILURE:
                        result = -1;
                        break;
                    case FAILURE:
                        result = -2;
                        break;
                    case SUCCESS:
                        if(cycle != NULL)free(cycle);
                        result = end.QuadPart - start.QuadPart;
                        break;
                }
            }
            break;
        }
    }
    return result;
}