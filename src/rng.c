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

status_t genHamiltonianU(char** matrix, int n, unsigned int percentFull, int* P) {
    unsigned int m = percentFull * n * (n - 1) / 200;
    unsigned int edgeCount = 0;
    for(int i = 1; i < n; i++) {
        matrix[P[i - 1] - OFFSET][P[i] - OFFSET] = 1;
        matrix[P[i] - OFFSET][P[i - 1] - OFFSET] = 1;
        edgeCount++;
    }
    matrix[P[n - 1] - OFFSET][P[0] - OFFSET] = 1;
    matrix[P[0] - OFFSET][P[n - 1] - OFFSET] = 1;
    edgeCount++;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(edgeCount <= m && matrix[i][j] == 0) {
                if((unsigned int)rand() % 100 < percentFull) {
                    matrix[i][j] = 1;
                    matrix[j][i] = 1;
                    edgeCount++;
                }
            }
        }
    }
    return SUCCESS;
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
            if(edgeCount <= m && matrix[i][j] == 0) {
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

status_t genNonHamiltonianU(char** matrix, int n, unsigned int percentFull) {
    /* unsigned int m = percentFull * n * (n - 1) / 200;
    unsigned int edgeCount = 0;
    for(int i = 1; i < n / 2; i++) {
        matrix[P[i - 1] - OFFSET][P[i] - OFFSET] = 1;
        matrix[P[i] - OFFSET][P[i - 1] - OFFSET] = 1;
        edgeCount++;
    }
    for(int i = n / 2 + 1; i < n; i++) {
        matrix[P[i - 1] - OFFSET][P[i] - OFFSET] = 1;
        matrix[P[i] - OFFSET][P[i - 1] - OFFSET] = 1;
        edgeCount++;
    }
    // matrix[P[n - 1] - OFFSET][P[0] - OFFSET] = 1;
    // matrix[P[0] - OFFSET][P[n - 1] - OFFSET] = 1;
    // edgeCount++;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(edgeCount <= m && matrix[i][j] == 0 &&
            (i != P[n - 1] - OFFSET || i != P[0] - OFFSET) &&
            (j != P[n - 1] - OFFSET || j != P[0] - OFFSET)) {
                if((unsigned int)rand() % 100 < percentFull) {
                    matrix[i][j] == 1;
                    matrix[j][i] == 1;
                    edgeCount++;
                }
            }
        }
    }
    return SUCCESS; */
    unsigned int m = percentFull * n * (n - 1) / 200;
    unsigned int edgeCount = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(edgeCount >= m)break;
            int r = rand() % 100;
            if((unsigned int)r < percentFull) {
                matrix[i][j] = 1;
                matrix[j][i] = 1;
                edgeCount++;
            }
        }
    }
    for(int j = 0; j < n; j++) {
        matrix[0][j] = 0;
        matrix[j][0] = 0;
    }
    matrix[0][n/2] = 1;
    matrix[n/2][0] = 1;
    
    return SUCCESS;
}

status_t genNonHamiltonianD(char** matrix, int n, unsigned int percentFull) {
    unsigned int m = percentFull * n * (n - 1) / 100;
    unsigned int edgeCount = 0;
    /* for(int i = 1; i < n; i++) { //using this permutation we make a Hamiltonian cycle
        matrix[P[i - 1] - OFFSET][P[i] - OFFSET] = 1;
        matrix[P[i] - OFFSET][P[i - 1] - OFFSET] = -1;
        edgeCount++;
    } */
    // matrix[P[n - 1] - 1][P[0] - 1] = 1;
    // matrix[P[0] - 1][P[n - 1] - 1] = -1;
    // edgeCount++;

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(edgeCount >= m)break;
            int r = rand() % 100;
            if((unsigned int)r < percentFull) {
                matrix[i][j] = 1;
                matrix[j][i] = -1;
                edgeCount++;
            }
        }
    }
    return SUCCESS;
}


status_t genEulerianU(char** matrix, int n, unsigned int percentFull, int* edges) {
    if(n % 2 == 1)return FAILURE; //Eulerian circuit is impossible 
    unsigned int m = percentFull * n * (n - 1) / 200;
    unsigned int edgeCount = 0;

    int* degrees = calloc(n, sizeof(int));
    if(degrees == NULL)return MEMORY_FAILURE;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(edgeCount < m && i != j && matrix[i][j] == 0) {
                if((unsigned int)rand() % 100 < percentFull) {
                    matrix[i][j] = 1;
                    matrix[j][i] = 1;
                    degrees[i]++;
                    degrees[j]++;
                    edgeCount++;
                }
            }
        }
        
    }

    for(int i = 0; i < n; i++) {
        if(degrees[i] % 2 == 1) {
            for(int j = 0; j < n; j++) {
                if(i != j && matrix[i][j] == 1 && degrees[j] % 2 == 1) {
                    matrix[i][j] = matrix[j][i] = 0;
                    edgeCount--;
                    degrees[i]--;
                    degrees[j]--;
                    break;
                }
            }
        }
    }

    for(int i = 0; i < n; i++) {
        if(degrees[i] % 2 == 1) {
            for(int j = 0; j < n; j++) {
                if(i != j && degrees[j] % 2 == 1) {
                    matrix[i][j] = matrix[j][i] = 1;
                    edgeCount++;
                    degrees[i]++;
                    degrees[j]++;
                    break;
                }
            }
        }
    }

    free(degrees);
    *edges = edgeCount;
    return SUCCESS;
}

status_t genEulerianD(char** matrix, int n, unsigned int percentFull, int* edges) {
    unsigned int m = percentFull * n * (n - 1) / 200;
    unsigned int edgeCount = 0;

    int* inDegrees = calloc(n, sizeof(int));
    int* outDegrees = calloc(n, sizeof(int));

    int e;
    genEulerianU(matrix, n, percentFull, &e);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(edgeCount < m && i != j && matrix[i][j] == 1) {
                if(rand() % 2 == 0) {
                    matrix[i][j] = -1;
                    inDegrees[i]++;
                    outDegrees[j]++;
                    edgeCount++;
                }
            }
        }
    }

}


status_t genNonEulerianU(char** matrix, int n, unsigned int percentFull, int* edges) {
    status_t s = genEulerianU(matrix, n, percentFull, edges);
    if(s == MEMORY_FAILURE)return MEMORY_FAILURE;
    int l = rand() % n, r = rand() % n;
    while(matrix[l][r] == 0) {
        l = rand() % n;
        r = rand() % n;
    }

    matrix[l][r] = 0;
    matrix[r][l] = 0;
    return SUCCESS;
}