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

static char hamiltonianA(ParametersA* parameters) {
    int current = parameters->current;
    parameters->visitedTable[current - OFFSET] = true;
    parameters->numVisited++;
    
    for(int j = 0; j < parameters->numberOfVertices; j++) {
        if(parameters->adjacencyMatrix[current - OFFSET][j] == true) {
            if(j + OFFSET == parameters->start && parameters->numVisited == parameters->numberOfVertices) {
                parameters->path[parameters->sp] = parameters->start;
                return true;
            }
            if(parameters->visitedTable[j] == false) {
                parameters->current = j + OFFSET;
                parameters->path[parameters->sp] = j + OFFSET;
                parameters->sp++;
                if(hamiltonianA(parameters)) {
                    return true;
                }
                parameters->sp--;
            }
        }
    }

    parameters->visitedTable[current - OFFSET] = false;
    parameters->numVisited--;
    parameters->current = current;
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
    
    ParametersA params = {
        adjM,
        visited,
        stack,
        n,
        start,
        start,
        0,
        1
    };

    char cycle = hamiltonianA(&params);
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

static char hamiltonianM(ParametersM* parameters) {
    int current = parameters->current;
    parameters->visitedTable[current - OFFSET] = true;
    parameters->numVisited++;
    
    int successor = parameters->graphMatrix[current - OFFSET][parameters->numberOfVertices];
    if(successor == OFFSET - 1)return false;
    
    int previous = OFFSET - 1;
    while(previous != successor) {
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
    }
    do {

    }
    while(parameters->graphMatrix[current - OFFSET][successor - OFFSET] != successor);

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