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
                current = j + OFFSET;
                path[sp] = j + OFFSET;
                sp++;
                if(hamiltonianA(adjacencyMatrix, visitedTable, path, numberOfVertices, start, current, numVisited, sp)) {
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
} ParametersM;

char hamiltonianM(ParametersM* parameters) {
    int current = parameters->current;
    parameters->visitedTable[current - OFFSET] = true;
    parameters->numVisited++;
    
    int successor;
    int cycleCheck = parameters->graphMatrix[current - OFFSET][parameters->numberOfVertices + 3];
    if(cycleCheck != OFFSET - 1)successor = cycleCheck;
    else successor = parameters->graphMatrix[current - OFFSET][parameters->numberOfVertices];

    if(successor == OFFSET - 1)return false; //no successor
    
    int previous = OFFSET - 1;

    for(int i = 0; i < parameters->numberOfVertices; i++) {
        if(successor == parameters->start && parameters->numVisited == parameters->numberOfVertices) {
            parameters->path[parameters->sp] = parameters->start;
            return true;
        }
        if(!parameters->visitedTable[successor - OFFSET]) {
            parameters->current = successor;
            parameters->path[parameters->sp] = successor;
            parameters->sp++;
            if(hamiltonianM(parameters)) return true;
            parameters->sp--;
        }

        previous = successor;
        successor = parameters->graphMatrix[current - OFFSET][successor - OFFSET];
        if(previous == successor)break;
    }
    /* while(previous != successor) {
        if(successor == parameters->start && parameters->numVisited == parameters->numberOfVertices) {
            parameters->path[parameters->sp] = parameters->start;
            return true;
        }
        if(!parameters->visitedTable[successor - OFFSET]) {
            parameters->current = successor;
            parameters->path[parameters->sp] = successor;
            parameters->sp++;
            if(hamiltonianM(parameters)) return true;
            parameters->sp--;
        }

        previous = successor;
        int cycleCheck = parameters->graphMatrix[current - OFFSET][successor - OFFSET] - 2 * parameters->numberOfVertices;
        if(cycleCheck > 0 && !parameters->visitedTable[cycleCheck - OFFSET]) {
            successor = cycleCheck;
        }
        else if(cycleCheck > 0 && parameters->visitedTable[cycleCheck - OFFSET]) {
            for(int j = successor - OFFSET + 1; j < parameters->numberOfVertices; j++) {
                if(parameters->graphMatrix[current - OFFSET][j] > 0) {
                    successor = parameters->graphMatrix[current - OFFSET][j];
                    break;
                }
            }
        }
        else successor = parameters->graphMatrix[current - OFFSET][successor - OFFSET];
    } */

    parameters->visitedTable[current - OFFSET] = false;
    parameters->numVisited--;
    parameters->current = current;

    return false;
}

status_t HamiltonianCycleM(int** grM, int n, int start, int** placeholder) {
    int* stack = calloc(n + 1, sizeof(int));
    if(stack == NULL)return MEMORY_FAILURE;
    
    char* visited = calloc(n, sizeof(char));
    if(visited == NULL) {
        free(stack);
        return MEMORY_FAILURE;
    }

    stack[0] = start;
    
    ParametersM params = {
        grM,
        visited,
        stack,
        n,
        start,
        start,
        0,
        1
    };

    char cycle = hamiltonianM(&params);
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