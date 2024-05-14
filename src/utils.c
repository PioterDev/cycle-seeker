#include <stdio.h>
#include <stdlib.h>

#include "structs_unions_defines.h"

void printArray(char* arr, int n) {
    for(int i = 0; i < n; i++) {
        if(arr[i] < 0)printf("%d ", arr[i]);
        else printf(" %d ", arr[i]);
    }
    printf("\n");
}

void printArrayInt(int* arr, int n, char* separator) {
    for(int i = 0; i < n - 1; i++) {
        printf("%d%s", arr[i], separator);
    }
    printf("%d\n", arr[n - 1]);
}

void printMatrix(char** matrix, int h, int w) {
    for(int i = 0; i < h; i++) {
        printArray(matrix[i], w);
    }
}

/* void printMatrixInt(int** matrix, int h, int w, char* separator) {
    for(int i = 0; i < h; i++) {
        printArrayInt(matrix[i], w, separator);
    }
} */

void printMatrixInt(int** matrix, int h, int w, int padding, char* separator) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int numDigits = 1;
            int num = matrix[i][j];
            while (num / 10 != 0) {
                num /= 10;
                numDigits++;
            }
            for (int k = 0; k < padding - numDigits; k++) printf(" ");
            if (matrix[i][j] >= 0) printf(" ");
            printf("%d%s", matrix[i][j], separator);
        }
        printf("\n");
    }
}

void printList(int** list, int h, char* separator) {
    for(int i = 0; i < h; i++) {
        int j = 0;
        printf("%d%s", i + OFFSET, separator);
        if(list[i][0] == OFFSET - 1) {
            printf("Nothing\n");
            continue;
        }
        while(list[i][j + 1] != OFFSET - 1) {
            printf("%d%s", list[i][j], separator);
            j++;
        }
        printf("%d\n", list[i][j]);
    }
}

char** zeroMatrix(int h, int w) {
    char** matrix = malloc(sizeof(char*) * h);
    if(matrix == NULL)return NULL;
    for(int i = 0; i < h; i++) {
        matrix[i] = calloc(w, sizeof(char));
        if(matrix[i] == NULL) {
            for(int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

char** copyMatrix(char** matrix, int h, int w) {
    char** M = malloc(sizeof(char*) * h);
    if(M == NULL)return NULL;
    
    for(int i = 0; i < h; i++) {
        M[i] = malloc(w);
        if(M[i] == NULL) {
            for(int j = 0; j < i; j++) {
                free(M[j]);
            }
            free(M);
            return NULL;
        }
        for(int j = 0; j < w; j++) {
            M[i][j] = matrix[i][j];
        }
    }

    return M;
}

void deallocMatrix(char** matrix, int h) {
    for(int i = 0; i < h; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void deallocMatrixInt(int** matrix, int h) {
    for(int i = 0; i < h; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int** matrixToSuccessorList(char** matrix, int n) {
    int** successorList = malloc(sizeof(int*) * n);
    if(successorList == NULL)return NULL;
    for(int i = 0; i < n; i++) {
        int successorAmount = 1;
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] > 0)successorAmount++;
        }
        successorList[i] = malloc(sizeof(int) * successorAmount);
        if(successorList[i] == NULL) {
            for(int k = 0; k < i; k++) {
                free(successorList[k]);
            }
            free(successorList);
            return NULL;
        }
        successorList[successorAmount - 1] = OFFSET - 1;
        int k = 0;
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] > 0) {
                successorList[i][k] = j + OFFSET;
                k++;
            }
        }
    }
    return successorList;
}

int** matrixToPredecessorList(char** matrix, int n) {
    int** predecessorList = malloc(sizeof(int*) * n);
    if(predecessorList == NULL)return NULL;
    for(int i = 0; i < n; i++) {
        int predecessorAmount = 1;
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] < 0)predecessorAmount++;
        }
        predecessorList[i] = malloc(sizeof(int) * predecessorAmount);
        if(predecessorList[i] == NULL) {
            for(int k = 0; k < i; k++) {
                free(predecessorList[k]);
            }
            free(predecessorList);
            return NULL;
        }
        predecessorList[predecessorAmount - 1] = OFFSET - 1;
        int k = 0;
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] < 0) {
                predecessorList[i][k] = j + OFFSET;
                k++;
            }
        }
    }
    return predecessorList;
}

int** matrixToNoIncidenceList(char** matrix, int n) {
    int** noIncidenceList = malloc(sizeof(int*) * n);
    if(noIncidenceList == NULL)return NULL;
    for(int i = 0; i < n; i++) {
        int noIncidenceAmount = 1;
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] == 0)noIncidenceAmount++;
        }
        noIncidenceList[i] = malloc(sizeof(int) * noIncidenceAmount);
        if(noIncidenceList[i] == NULL) {
            for(int k = 0; k < i; k++) {
                free(noIncidenceList[k]);
            }
            free(noIncidenceList);
            return NULL;
        }
        noIncidenceList[noIncidenceAmount - 1] = OFFSET - 1;
        int k = 0;
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] == 0) {
                noIncidenceList[i][k] = j + OFFSET;
                k++;
            }
        }
    }
    return noIncidenceList;
}

status_t matrixToLists(char** matrix, int n, int*** buf) {
    int** successorList = malloc(sizeof(int*) * n);
    if(successorList == NULL)return MEMORY_FAILURE;

    int** predecessorList = malloc(sizeof(int*) * n);
    if(predecessorList == NULL) {
        free(successorList);
        return MEMORY_FAILURE;
    }

    int** noIncidenceList = malloc(sizeof(int*) * n);
    if(noIncidenceList == NULL) {
        free(successorList);
        free(predecessorList);
        return MEMORY_FAILURE;
    }

    for(int i = 0; i < n; i++) {
        int counter[3] = {1, 1, 1};
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] > 0)counter[0]++; //successor
            else if(matrix[i][j] < 0)counter[1]++; //predecessor
            else counter[2]++; //no incidence
        }

        successorList[i] = calloc(counter[0], sizeof(int));
        if(successorList[i] == NULL) {
            for(int k = 0; k < i; k++) {
                free(successorList[k]);
                free(predecessorList[k]);
                free(noIncidenceList[k]);
            }
            free(successorList);
            free(predecessorList);
            free(noIncidenceList);
            return MEMORY_FAILURE;
        }
        
        predecessorList[i] = calloc(counter[1], sizeof(int));
        if(predecessorList[i] == NULL) {
            for(int k = 0; k < i; k++) {
                free(successorList[k]);
                free(predecessorList[k]);
                free(noIncidenceList[k]);
            }
            free(successorList[i]);
            free(successorList);
            free(predecessorList);
            free(noIncidenceList);
            return MEMORY_FAILURE;
        }
        
        noIncidenceList[i] = calloc(counter[2], sizeof(int));
        if(predecessorList[i] == NULL) {
            for(int k = 0; k < i; k++) {
                free(successorList[k]);
                free(predecessorList[k]);
                free(noIncidenceList[k]);
            }
            free(successorList[i]);
            free(successorList);
            free(predecessorList[i]);
            free(predecessorList);
            free(noIncidenceList);
            return MEMORY_FAILURE;
        }

        successorList[i][counter[0] - 1] = OFFSET - 1;
        predecessorList[i][counter[1] - 1] = OFFSET - 1;
        noIncidenceList[i][counter[2] - 1] = OFFSET - 1;

        int iterator[3] = {0};
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] > 0)successorList[i][iterator[0]++] = j + OFFSET; //successor
            else if(matrix[i][j] < 0)predecessorList[i][iterator[1]++] = j + OFFSET; //predecessor
            else noIncidenceList[i][iterator[2]++] = j + OFFSET; //no incidence
        }
    }

    buf[0] = successorList;
    buf[1] = predecessorList;
    buf[2] = noIncidenceList;

    return SUCCESS;
}

int** graphMatrixFrom(int n, int** successorList, int** predecessorList, int** noIncidenceList) {
    int** M = malloc(sizeof(int*) * n);
    if(M == NULL)return NULL;
    for(int i = 0; i < n; i++) {
        M[i] = calloc(n + 4, sizeof(int));
        if(M[i] == NULL) {
            for(int j = 0; j < i; j++) {
                free(M[i]);
            }
            free(M);
            return NULL;
        }
    }

    //Krok #1
    for(int i = 0; i < n; i++) {
        if(successorList[i][0] == OFFSET - 1) M[i][n] = OFFSET - 1; //brak nastepnika
        else M[i][n] = successorList[i][0]; //pierwszy nastepnik
    }
    for(int i = 0; i < n; i++) {
        int j = 0;
        while(successorList[i][j] != OFFSET - 1) {
            if(successorList[i][j + 1] == OFFSET - 1) {
                M[i][successorList[i][j] - OFFSET] = successorList[i][j];
                break;
            }
            else {
                M[i][successorList[i][j] - OFFSET] = successorList[i][j + 1];
            }
            j++;
        }
    }

    //Krok #2
    for(int i = 0; i < n; i++) {
        if(predecessorList[i][0] == OFFSET - 1)M[i][n + 1] = OFFSET - 1; //brak poprzednika
        else M[i][n + 1] = predecessorList[i][0]; //pierwszy poprzednik
    }
    for(int i = 0; i < n; i++) {
        int j = 0;
        while(predecessorList[i][j] != OFFSET - 1) {
            if(predecessorList[i][j + 1] == OFFSET - 1) {
                M[i][predecessorList[i][j] - OFFSET] = predecessorList[i][j] + n;
                break;
            }
            else {
                M[i][predecessorList[i][j] - OFFSET] = predecessorList[i][j + 1] + n;
            }
            j++;
        }
    }

    //Krok #3
    for(int i = 0; i < n; i++) {
        if(noIncidenceList[i][0] == OFFSET - 1)M[i][n + 2] = OFFSET - 1; //brak braku incydentnego wierzchola
        else M[i][n + 2] = noIncidenceList[i][0];
    }
    for(int i = 0; i < n; i++) {
        int j = 0;
        while(noIncidenceList[i][j] != OFFSET - 1) {
            if(noIncidenceList[i][j + 1] == OFFSET - 1) {
                M[i][noIncidenceList[i][j] - OFFSET] = -1 * noIncidenceList[i][j];
                break;
            }
            else {
                M[i][noIncidenceList[i][j] - OFFSET] = -1 * noIncidenceList[i][j + 1];
            }
            j++;
        }
    }

    return M;
}