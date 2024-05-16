#include <stdio.h>
#include <stdlib.h>

#include "structs_unions_defines.h"
#include "utils.h"
typedef struct ParamsA {
    char** adjacencyMatrix;
    int numberOfVertices;
    int numberOfEdges;
    int* stack;
    int sp;
    int current;
} ParametersA;

void DFS_Euler(ParametersA* parameters) {
    int current = parameters->current;
    printf("%d\n", current);
    for(int j = 0; j < parameters->numberOfVertices; j++) {
        if(parameters->adjacencyMatrix[current - OFFSET][j] == 1) {
            parameters->adjacencyMatrix[current - OFFSET][j] = 0;
            parameters->adjacencyMatrix[j][current - OFFSET] = 0;
            parameters->current = j + OFFSET;
            DFS_Euler(parameters);
        }
    }
    parameters->stack[parameters->sp] = current;
    parameters->sp++;
}

status_t EulerianCircuitA(char** adjM, int n, int m, int start, int** placeholder) {
    char** adjMcopy = copyMatrix(adjM, n, n);
    if(adjMcopy == NULL)return MEMORY_FAILURE;

    int* stack = malloc(sizeof(int) * m);
    if(stack == NULL) {
        deallocMatrix(adjMcopy, n);
        return MEMORY_FAILURE;
    }

    ParametersA params = {
        adjMcopy,
        n,
        m,
        stack,
        0,
        start
    };

    DFS_Euler(&params);

    deallocMatrix(adjMcopy, n);
    if(params.sp == m + 1) {
        *placeholder = stack;
        return SUCCESS;
    }
    else return FAILURE;
}




typedef struct {
    int** graphMatrix;
    char** deletedMatrix;
    int numberOfVertices;
    int numberOfEdges;
    int* stack;
    int sp;
    int current;
} ParametersM;

void DFS_EulerM(ParametersM* parameters) {
    int current = parameters->current;
    
    if(parameters->graphMatrix[current - OFFSET][parameters->numberOfVertices] == OFFSET - 1)goto end;

    int successor = parameters->graphMatrix[current - OFFSET][parameters->numberOfVertices];
    int previous = OFFSET - 1;
    while(previous != successor) {
        if(!parameters->deletedMatrix[current - OFFSET][successor - OFFSET] && !parameters->deletedMatrix[successor - OFFSET][current - OFFSET]) {
            parameters->deletedMatrix[current - OFFSET][successor - OFFSET] = 1;
            parameters->deletedMatrix[successor - OFFSET][current - OFFSET] = 1;
            
            parameters->current = successor;
            
            DFS_EulerM(parameters);
        }

        previous = successor;        
        int cycleCheck = parameters->graphMatrix[current - OFFSET][successor - OFFSET] - 2 * parameters->numberOfVertices;
        if(cycleCheck > 0)successor = cycleCheck;
        else successor = parameters->graphMatrix[current - OFFSET][successor - OFFSET];
    }

    end:
        parameters->stack[parameters->sp] = current;
        parameters->sp++;
}

status_t EulerianCircuitM(int** grM, int n, int m, int start, int** placeholder) {
    char** deletedM = zeroMatrix(n, n);
    if(deletedM == NULL)return MEMORY_FAILURE;

    int* stack = calloc(m + 1, sizeof(int));
    if(stack == NULL) {
        free(deletedM);
        return MEMORY_FAILURE;
    }

    ParametersM params = {
        grM,
        deletedM,
        n,
        m,
        stack,
        0,
        start
    };

    DFS_EulerM(&params);

    if(params.sp == m + 1) {
        *placeholder = stack;
        return SUCCESS;
    }
    else {
        free(stack);
        return FAILURE;
    }
}