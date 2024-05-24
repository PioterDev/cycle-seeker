#include <stdio.h>
#include <stdlib.h>

#include "structs_unions_defines.h"
#include "utils.h"

typedef struct ParametersA {
    int current;
    char** adjacencyMatrix;
    int numberOFVertices;
    int* path;
    int sp;
} ParametersA;

void DFS_EulerA(ParametersA* parameters) {
    int current = parameters->current;
    for(int j = 0; j < parameters->numberOFVertices; j++) {
        if(parameters->adjacencyMatrix[current - OFFSET][j] == 1) {
            parameters->adjacencyMatrix[current - OFFSET][j] = -1;
            parameters->adjacencyMatrix[j][current - OFFSET] = -1;
            // printf("Going to %d\n", j + OFFSET);
            parameters->current = j + OFFSET;
            DFS_EulerA(parameters);
        }
    }
    parameters->path[parameters->sp] = current;
    parameters->sp++;
    // printf("%d\n", *sp);
}

status_t EulerianCircuitA(char** adjM, int n, int m, int start, int** placeholder) {
    int* path = malloc(sizeof(int) * (m + 1));
    if(path == NULL)return MEMORY_FAILURE;
    // printf("%d\n", m);

    ParametersA params = {
        start,
        adjM,
        n,
        path,
        0
    };
    DFS_EulerA(&params);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(adjM[i][j] == -1)adjM[i][j] = 1;
        }
    }
    if(params.sp == m + 1) {
        path[m] = start;
        *placeholder = path;
        return SUCCESS;
    }
    else {
        free(path);
        return FAILURE;
    }
}



void DFS_EulerM(int v, int** grM, int n, int* path, int* sp, char** workingCopy) {
    int successor = grM[v - OFFSET][n];
    int previous = OFFSET - 1;
    while(previous != successor) {
        if(workingCopy[v - OFFSET][successor - OFFSET] == 0) {
            workingCopy[v - OFFSET][successor - OFFSET] = 1;
            workingCopy[successor - OFFSET][v - OFFSET] = 1;
            DFS_EulerM(successor, grM, n, path, sp, workingCopy);
        }
        previous = successor;
        successor = grM[v - OFFSET][successor - OFFSET];
    }
    path[*sp] = v;
    (*sp)++;
}

status_t EulerianCircuitM(int** grM, int n, int m, int start, int** placeholder) {
    int* path = malloc(sizeof(int) * (m + 1));
    if(path == NULL)return MEMORY_FAILURE;

    char** addM = zeroMatrix(n, n);
    if(addM == NULL) {
        free(path);
        return MEMORY_FAILURE;
    }

    int sp = 0;

    DFS_EulerM(start, grM, n, path, &sp, addM);
    free(addM);
    if(sp == m + 1) {
        path[m] = start;
        reverseArrayInt(path, m + 1);
        *placeholder = path;
        return SUCCESS;
    }
    else {
        free(path);
        return FAILURE;
    }
}