#include <stdio.h>
#include <stdlib.h>

#include "structs_unions_defines.h"
#include "utils.h"

typedef struct ParamsA {
    char** adjacencyMatrix;
    char* visitedTable;
    int* path;
    int numberOfVertices;
    int start;
    int current;
    int numVisited;
    int sp;
} ParametersA;

char hamiltonianA(char** adjacencyMatrix, char* visitedTable, int* path, const int numberOfVertices, const int start, int current, int numVisited, int sp) {
    visitedTable[current - OFFSET] = true;
    numVisited++;
    
    for(int j = 0; j < numberOfVertices; j++) {
        if(adjacencyMatrix[current - OFFSET][j] == true) {
            if(j + OFFSET == start && numVisited == numberOfVertices) {
                path[sp] = start;
                return true;
            }
            if(visitedTable[j] == false) {
                path[sp] = j + OFFSET;
                sp++;
                if(hamiltonianA(adjacencyMatrix, visitedTable, path, numberOfVertices, start, j + OFFSET, numVisited, sp)) {
                    return true;
                }
                sp--;
            }
        }
    }

    visitedTable[current - OFFSET] = false;
    numVisited--;
    return false;
}

status_t HamiltonianCycleA(char** adjM, int n, int start, int** placeholder) {
    int* stack = calloc(n + 1, sizeof(int));
    if(stack == NULL)return MEMORY_FAILURE;
    
    char* visited = calloc(n, sizeof(char));
    if(visited == NULL) {
        free(stack);
        return MEMORY_FAILURE;
    }

    stack[0] = start;
    
    char cycle = hamiltonianA(adjM, visited, stack, n, start, start, 0, 1);
    free(visited);
    if(!cycle) {
        free(stack);
        return FAILURE;
    }
    else {
        *placeholder = stack;
        return SUCCESS;
    }
    return FAILURE;
}





typedef struct ParamsM {
    int** graphMatrix;
    char* visitedTable;
    int* path;
    int numberOfVertices;
    int start;
    int current;
    int numVisited;
    int sp;
    FILE* debug;
} ParametersM;

char hamiltonianM(int** graphMatrix, char* visitedTable, int* path, const int numberOfVertices, const int start, int current, int numVisited, int sp, FILE* debug) {
    visitedTable[current - OFFSET] = true;
    numVisited++;

    int successor;
    /* int cycleCheck = parameters->graphMatrix[current - OFFSET][parameters->numberOfVertices + 3];
    if(cycleCheck != OFFSET - 1)successor = cycleCheck;
    else */ successor = graphMatrix[current - OFFSET][numberOfVertices];

    if(debug != NULL)fprintf(debug, "Current: %d, successor: %d\n", current, successor);

    if(successor == OFFSET - 1) {
        return false; //no successor
    }
    
    int previous = OFFSET - 1;

    while(previous != successor) {
        if(successor == start && numVisited == numberOfVertices) {
            path[sp] = start;
            return true;
        }
        if(!visitedTable[successor - OFFSET]) {
            path[sp] = successor;
            sp++;
            if(debug != NULL)fprintf(debug, "Going to %d\n", successor);
            if(hamiltonianM(graphMatrix, visitedTable, path, numberOfVertices, start, successor, numVisited, sp, debug)) return true;
            sp--;
        }

        previous = successor;
        /* int cycleCheck = parameters->graphMatrix[current - OFFSET][successor - OFFSET] - 2 * parameters->numberOfVertices;
        if(cycleCheck > 0) {
            successor = cycleCheck;
        }
        else  */successor = graphMatrix[current - OFFSET][successor - OFFSET];
        if(debug != NULL)fprintf(debug, "Found %d\n", successor);
    }

    visitedTable[current - OFFSET] = false;
    numVisited--;
    if(debug != NULL)fprintf(debug, "Going back to %d\n", current);
    return false;
}

status_t HamiltonianCycleM(int** grM, int n, int start, int** placeholder, FILE* debug) {
    int* stack = calloc(n + 1, sizeof(int));
    if(stack == NULL)return MEMORY_FAILURE;
    
    char* visited = calloc(n, sizeof(char));
    if(visited == NULL) {
        free(stack);
        return MEMORY_FAILURE;
    }

    stack[0] = start;
    
    /* ParametersM params = {
        grM,
        visited,
        stack,
        n,
        start,
        start,
        0,
        1,
        debug
    }; */

    char cycle = hamiltonianM(grM, visited, stack, n, start, start, 0, 1, debug);
    free(visited);
    if(!cycle) {
        free(stack);
        return FAILURE;
    }
    else {
        *placeholder = stack;
        return SUCCESS;
    }
    return FAILURE;
}