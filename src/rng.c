#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "structs_unions_defines.h"
#include "utils.h"

static inline void swap(int* x, int* y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int* sequence(int n) {
    int* seq = malloc(sizeof(int) * n);
    if(seq == NULL)return NULL;

    for(int i = 0; i < n; i++) {
        seq[i] = i + 1;
    }
    return seq;
}

int* permute(int* arr, int n) {
    int* permutation = malloc(sizeof(int) * n);
    if(permutation == NULL)return NULL;

    for(int i = 0; i < n; i++) {
        permutation[i] = arr[i];
    }
    
    for(int i = n - 1; i > 0; i--) {
        int r = rand() % (i + 1);
        swap(&permutation[r], &permutation[i]);
    }

    return permutation;
}

status_t genHamiltonianU(char** matrix, int n, int m, int* P) {
    int edgeCount = 0;
    for(int i = 1; i < n; i++) {
        matrix[P[i - 1]][P[i]] = 1;
        matrix[P[i]][P[i - 1]] = 1;
        edgeCount++;
    }
    matrix[P[n - 1]][P[0]] = 1;
    matrix[P[0]][P[n - 1]] = 1;
    edgeCount++;

    while(edgeCount < m) {

    }
}

status_t genHamiltonianD(char** matrix, int n, unsigned int percentFull, int* P) {
    unsigned int m = percentFull * n * (n - 1) / 100;
    unsigned int edgeCount = 0;
    for(int i = 1; i < n; i++) { //using this permutation we make a Hamiltonian cycle
        matrix[P[i - 1] - 1][P[i] - 1] = 1;
        matrix[P[i] - 1][P[i - 1] - 1] = -1;
        edgeCount++;
    }
    matrix[P[n - 1] - 1][P[0] - 1] = 1;
    matrix[P[0] - 1][P[n - 1] - 1] = -1;
    edgeCount++;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(edgeCount <= m) {
                if((unsigned int)rand() % 100 < percentFull) {
                    matrix[i][j] = 1;
                    matrix[j][i] = -1;
                    edgeCount++;
                }
            }
        }
    }
    return SUCCESS;
}