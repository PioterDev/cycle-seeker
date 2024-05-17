#include <stdio.h>
#include <stdlib.h>

#include "structs_unions_defines.h"

void printArray(char* arr, int n, FILE* stream) {
    for(int i = 0; i < n; i++) {
        if(arr[i] < 0)fprintf(stream, "%d ", arr[i]);
        else fprintf(stream, " %d ", arr[i]);
    }
    fprintf(stream, "\n");
}

void printArrayInt(int* arr, int n, char* separator, FILE* stream) {
    for(int i = 0; i < n - 1; i++) {
        fprintf(stream, "%d%s", arr[i], separator);
    }
    fprintf(stream, "%d\n", arr[n - 1]);
}

void printMatrix(char** matrix, int h, int w, FILE* stream) {
    for(int i = 0; i < h; i++) {
        printArray(matrix[i], w, stream);
    }
}

/* void printMatrixInt(int** matrix, int h, int w, char* separator) {
    for(int i = 0; i < h; i++) {
        printArrayInt(matrix[i], w, separator);
    }
} */

void printMatrixInt(int** matrix, int h, int w, int padding, char* separator, FILE* stream) {
    for (int i = 0; i < h; i++) {
        fprintf(stream, "%d | ", i + 1);
        for (int j = 0; j < w; j++) {
            int numDigits = 1;
            int num = matrix[i][j];
            while (num / 10 != 0) {
                num /= 10;
                numDigits++;
            }
            for (int k = 0; k < padding - numDigits; k++) fprintf(stream, " ");
            if (matrix[i][j] >= 0) fprintf(stream, " ");
            fprintf(stream, "%d%s", matrix[i][j], separator);
        }
        fprintf(stream, "\n");
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
    if(successorList == NULL)goto failure;

    int** predecessorList = malloc(sizeof(int*) * n);
    if(predecessorList == NULL)goto failure_s;

    int** noIncidenceList = malloc(sizeof(int*) * n);
    if(noIncidenceList == NULL)goto failure_p;

    int** cycleList = malloc(sizeof(int*) * n);
    if(cycleList == NULL)goto failure_n;

    for(int i = 0; i < n; i++) {
        int counter[4] = {1, 1, 1, 1};
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] > 0 && matrix[j][i] > 0) {
                counter[3]++;
                continue;
            }
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
                free(cycleList[k]);
            }

            goto failure_c;
        }
        
        predecessorList[i] = calloc(counter[1], sizeof(int));
        if(predecessorList[i] == NULL) {
            for(int k = 0; k < i; k++) {
                free(successorList[k]);
                free(predecessorList[k]);
                free(noIncidenceList[k]);
                free(cycleList[k]);
            }
            free(successorList[i]);

            goto failure_c;
        }
        
        noIncidenceList[i] = calloc(counter[2], sizeof(int));
        if(predecessorList[i] == NULL) {
            for(int k = 0; k < i; k++) {
                free(successorList[k]);
                free(predecessorList[k]);
                free(noIncidenceList[k]);
                free(cycleList[k]);
            }
            free(successorList[i]);
            free(predecessorList[i]);
            
            goto failure_c;
        }

        cycleList[i] = calloc(counter[3], sizeof(int));
        if(cycleList[i] == NULL) {
            for(int k = 0; k < i; k++) {
                free(successorList[k]);
                free(predecessorList[k]);
                free(noIncidenceList[k]);
                free(cycleList[k]);
            }
            free(successorList[i]);
            free(predecessorList[i]);
            free(noIncidenceList[i]);

            goto failure_c;
        }

        successorList[i][counter[0] - 1] = OFFSET - 1;
        predecessorList[i][counter[1] - 1] = OFFSET - 1;
        noIncidenceList[i][counter[2] - 1] = OFFSET - 1;
        cycleList[i][counter[3] - 1] = OFFSET - 1;

        int iterator[4] = {0};
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] > 0 && matrix[j][i] > 0) {
                cycleList[i][iterator[3]++] = j + OFFSET;
                continue;
            }
            else if(matrix[i][j] > 0)successorList[i][iterator[0]++] = j + OFFSET; //successor
            else if(matrix[i][j] < 0)predecessorList[i][iterator[1]++] = j + OFFSET; //predecessor
            else noIncidenceList[i][iterator[2]++] = j + OFFSET; //no incidence
        }
    }

    buf[0] = successorList;
    buf[1] = predecessorList;
    buf[2] = noIncidenceList;
    buf[3] = cycleList;

    return SUCCESS;

    failure_c:
        free(cycleList);
    failure_n:
        free(noIncidenceList);
    failure_p:
        free(predecessorList);
    failure_s:
        free(successorList);
    failure:
        return MEMORY_FAILURE;
}

int** graphMatrixFrom(int n, int** successorList, int** predecessorList, int** noIncidenceList, int** cycleList) {
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

    //Krok #4
    for(int i = 0; i < n; i++) {
        if(cycleList[i][0] == OFFSET - 1)M[i][n + 3] = OFFSET - 1; //nie ma cyklu
        else M[i][n + 3] = cycleList[i][0];
    }
    for(int i = 0; i < n; i++) {
        int j = 0;
        while(cycleList[i][j] != OFFSET - 1) {
            if(cycleList[i][j + 1] == OFFSET - 1) {
                M[i][cycleList[i][j] - OFFSET] = 2 * n + cycleList[i][j];
                break;
            }
            else {
                M[i][cycleList[i][j] - OFFSET] = 2 * n + cycleList[i][j + 1];
            }
            j++;
        }
    }

    return M;
}