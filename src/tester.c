#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "euler.h"
#include "hamilton.h"
#include "rng.h"
#include "structs_unions_defines.h"
#include "utils.h"

long long test(char algorithm, char** adjacencyMatrix, int** graphMatrix, int vertices) {
    LARGE_INTEGER start, end;
    long long result;
    switch(algorithm) {
        case 'e': { //euler
            if(adjacencyMatrix != NULL) {

            }
            else if(graphMatrix != NULL) {
                
            }
            break;
        }
        case 'h': { //hamilton
            if(adjacencyMatrix != NULL) {
                int* cycle = NULL;
                QueryPerformanceCounter(&start);
                status_t hamilton = HamiltonianCycleA(adjacencyMatrix, vertices, 1, &cycle);
                QueryPerformanceCounter(&end);
                if(hamilton == MEMORY_FAILURE)result = -1;
                else {
                    if(cycle != NULL)free(cycle);
                    result = end.QuadPart - start.QuadPart;
                }
            }
            else if(graphMatrix != NULL) {
                int* cycle = NULL;
                QueryPerformanceCounter(&start);
                status_t hamilton = HamiltonianCycleM(graphMatrix, vertices, 1, &cycle);
                QueryPerformanceCounter(&end);
                if(hamilton == MEMORY_FAILURE)result = -1;
                else if(hamilton == FAILURE) {
                    result = -2;
                }
                else {
                    if(cycle != NULL)free(cycle);
                    result = end.QuadPart - start.QuadPart;
                }
            }
            break;
        }
    }
    return result;
}

DWORD WINAPI testThreaded(void* params) {
    Params* parameters = params;
    fprintf(parameters->file, "H;%d;%d;%lld;%lld\n", 
        parameters->n, 
        parameters->percentageFull,
        test('h', parameters->adjM, NULL, parameters->n),
        test('h', NULL, parameters->grM, parameters->n)
    );
    return 0;
}