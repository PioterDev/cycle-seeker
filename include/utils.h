#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Prints an array. Each element is interpreted as a char.
 * 
 * @param arr array
 * @param n length of the array
 */
void printArray(char* arr, int n);

/**
 * @brief Prints an array. Each element is interpreted as an integer.
 * 
 * @param arr array
 * @param n length of the array
 * @param separator separator
 */
void printArrayInt(int* arr, int n, char* separator);

/**
 * @brief Prints a matrix of byte-size numbers. Each row is interpreted as an array of chars.
 * 
 * @param matrix matrix
 * @param m vertical size
 * @param n horizontal size
 */
void printMatrix(char** matrix, int m, int n);

/**
 * @brief Prints a matrix of ints.
 * 
 * @param matrix matrix
 * @param h vertical size
 * @param w horizontal size
 * @param padding how many spaces should be added to align "0" with the biggest number
 * @param separator separator
 */
void printMatrixInt(int** matrix, int rows, int cols, int padding, char* separator);

/**
 * @brief Prints a list (array of arrays that end with `OFFSET` - 1).
 * 
 * @param list list
 * @param h vertical size
 * @param separator separator
 */
void printList(int** list, int h, char* separator);

/**
 * @brief Dynamically creates a square matrix of bytes of given size.
 * 
 * @param h height of the matrix
 * @param w width of the matrix
 * @return pointer to copied matrix, NULL on memory allocation error
 */
char** zeroMatrix(int h, int w);

/**
 * @brief Copies a matrix of bytes.
 * 
 * @param matrix original matrix
 * @param h height of the matrix
 * @param w width of the matrix
 * @return pointer to copied matrix, NULL on memory allocation error
 */
char** copyMatrix(char** matrix, int h, int w);

/**
 * @brief Deallocates a dynamically created matrix of bytes of given height.
 * 
 * @param matrix matrix
 * @param h vertical size
 */
void deallocMatrix(char** matrix, int h);

/**
 * @brief Deallocates a dynamically created matrix of ints of given height.
 * 
 * @param matrix matrix
 * @param h vertical size
 */
void deallocMatrixInt(int** matrix, int h) ;

/**
 * @brief Returns a successor list of a graph converted from adjacency matrix representation.
 * 
 * @param matrix matrix
 * @param n number of vertices
 * @return pointer to successor list, NULL on error
 */
int** matrixToSuccessorList(char** matrix, int n);

/**
 * @brief Returns a predecessor list of a graph converted from adjacency matrix representation.
 * 
 * @param matrix matrix
 * @param n number of vertices
 * @return pointer to predecessor list, NULL on error
 */
int** matrixToPredecessorList(char** matrix, int n);

/**
 * @brief Returns a no-incidence list of a graph converted from adjacency matrix representation.
 * 
 * @param matrix matrix
 * @param n number of vertices
 * @return pointer to no-incidence list, NULL on error
 */
int** matrixToNoIncidenceList(char** matrix, int n);

/**
 * @brief Combines matrixToSuccessorList, matrixToPredecessorList and matrixToNoIncidenceList. 
 * Puts results of all 3 into a triple pointer passed as a buffer.
 * 
 * @param matrix matrix
 * @param n number of vertices
 * @param buf array of size at least 3 of pointers to pointers
 * @return status_t 
 */
status_t matrixToLists(char** matrix, int n, int*** buf);

/**
 * @brief Creates a graph matrix representation of a graph from lists.
 * 
 * @param n number of vertices
 * @param successorList successor list
 * @param predecessorList predecessor list
 * @param noIncidenceList no-incidence list
 * @return pointer to the matrix, NULL on memory allocation error
 */
int** graphMatrixFrom(int n, int** successorList, int** predecessorList, int** noIncidenceList);


#endif