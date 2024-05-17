#ifndef STRUCTS_UNIONS_H
#define STRUCTS_UNIONS_H

#define OFFSET 1
#define true 1
#define false 0

typedef enum status_t {
    SUCCESS,
    FAILURE,
    MEMORY_FAILURE
} status_t;

typedef struct Params {
    FILE* file;
    char** adjM;
    int** grM;
    int n;
    int percentageFull;
    FILE* debug;
} Params;


#endif