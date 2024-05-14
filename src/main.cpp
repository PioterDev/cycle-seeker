#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

#include "euler.h"
#include "eulerAdj.h"
#include "eulerMat.h"
#include "hamilton.h"
#include "structs_unions_defines.h"
#include "utils.h"

#define nl() printf("\n") //Prints a new line

void cycleAdjacencyMatrix(char** matrix, GraphAdj graph, int n) {
    wprintf(L"Wybierz poszukiwany cykl.\n\n");
    wprintf(L"Dla Hamiltona, wpisz 'h'\n");
    wprintf(L"Dla Eulera, wpisz 'e'\n");
    printf("Wybrana opcja: ");

    char option;
    scanf("\n%c", &option);

    switch(option) {
        case 'h': {
            int* cycle = NULL;
            status_t hamiltonianCycle = HamiltonianCycleA(matrix, n, 1, &cycle);
            switch(hamiltonianCycle) {
                case SUCCESS: {
                    if(cycle != NULL) {
                        wprintf(L"Cykl: ");
                        printArrayInt(cycle, n + 1, " -> ");
                        free(cycle);
                    }
                    break;
                }
                case FAILURE: {
                    wprintf(L"Graf wejściowy nie zawiera cyklu.\n");
                    break;
                }
                case MEMORY_FAILURE: {
                    wprintf(L"Alokacja pamięci nie powiodła się.\n");
                    break;
                }
            }
            break;
        }
        case 'e': {
            graph.printEulerTour();
            break;
        }
    }
}

void cycleGraphMatrix(int** matrix, int n) {
    wprintf(L"Wybierz poszukiwany cykl.\n\n");
    wprintf(L"Dla Hamiltona, wpisz 'h'\n");
    wprintf(L"Dla Eulera, wpisz 'e'\n");
    printf("Wybrana opcja: ");

    char option;
    scanf("\n%c", &option);

    switch(option) {
        case 'h': {
            int* cycle = NULL;
            status_t hamiltonianCycle = HamiltonianCycleM(matrix, n, 1, &cycle);
            switch(hamiltonianCycle) {
                case SUCCESS: {
                    if(cycle != NULL) {
                        wprintf(L"Cykl: ");
                        printArrayInt(cycle, n + 1, " -> ");
                        free(cycle);
                    }
                    break;
                }
                case FAILURE: {
                    wprintf(L"Graf wejściowy nie zawiera cyklu.\n");
                    break;
                }
                case MEMORY_FAILURE: {
                    wprintf(L"Alokacja pamięci nie powiodła się.\n");
                    break;
                }
            }
            break;
        }
        case 'e': {
            printf("Chilowo nie ma.\n");
            break;
        }
    }
}

void fromFile() {
    while(true) {
        wprintf(L"Podaj ścieżkę do pliku: ");
        char path[256];
        scanf("%255s", path);
        if(!strcmp(path, "q"))exit(0);
        if(!strcmp(path, "b")) {
            printf("\n\n\n");
            break;
        }
        nl();
        FILE* file = fopen(path, "r");
        if(file == NULL) {
            wprintf(L"Otwarcie pliku nie powiodło się.\n");
            continue;
        }
        int vertices = 0, edges = 0;
        fscanf(file, "%d %d", &vertices, &edges);

        wprintf(L"Wybierz reprezentację grafu.\n\n");
        wprintf(L"Dla macierzy sąsiedztwa, wpisz 'm'\n");
        wprintf(L"Dla macierzy grafu, wpisz 'g'\n");
        printf("Wybrana opcja: ");

        char option;
        scanf("\n%c", &option);

        switch(option) {
            case 'm': {
                GraphAdj graph(vertices);
                char** M = zeroMatrix(vertices, vertices);
                if(M == NULL) {
                    wprintf(L"Alokacja pamięci nie powiodła się.\n");
                    break;
                }

                int x1, x2;
                while(fscanf(file, "%d %d", &x1, &x2) == 2) {                    
                    M[x1 - OFFSET][x2 - OFFSET] = 1;
                    M[x2 - OFFSET][x1 - OFFSET] = 1;
                    graph.AddEdge(x1 - OFFSET, x2 - OFFSET);
                }
                printMatrix(M, vertices, vertices);
                cycleAdjacencyMatrix(M, graph, vertices);

                deallocMatrix(M, vertices);
                break;
            }
            case 'g': {
                //TODO: do zmiany
                char** M = zeroMatrix(vertices, vertices);
                if(M == NULL) {
                    wprintf(L"Alokacja pamięci nie powiodła się.\n");
                    break;
                }

                int x1, x2;
                while(fscanf(file, "%d %d", &x1, &x2) == 2) {                    
                    M[x1 - OFFSET][x2 - OFFSET] = 1;
                    M[x2 - OFFSET][x1 - OFFSET] = -1;
                }

                int** buf[3];
                if(matrixToLists(M, vertices, buf) == MEMORY_FAILURE) {
                    deallocMatrix(M, vertices);
                    wprintf(L"Alokacja pamięci nie powiodła się.\n");
                    break;
                };

                int** grM = graphMatrixFrom(vertices, buf[0], buf[1], buf[2]);
                deallocMatrixInt(buf[0], vertices);
                deallocMatrixInt(buf[1], vertices);
                deallocMatrixInt(buf[2], vertices);
                deallocMatrix(M, vertices);
                if(grM == NULL) {
                    wprintf(L"Alokacja pamięci nie powiodła się.\n");
                    break;
                }

                printMatrixInt(grM, vertices, vertices + 4, 2, " ");

                cycleGraphMatrix(grM, vertices);

                deallocMatrixInt(grM, vertices);

                break;
            }
            default: {
                wprintf(L"Nieznana opcja, spróbuj ponownie.\n");
                break;
            }
        }
    }
}

void fromKeyboard() {
    wprintf(L"Wybierz reprezentację grafu.\n\n");
    wprintf(L"Dla macierzy sąsiedztwa, wpisz 'm'\n");
    wprintf(L"Dla macierzy grafu, wpisz 'g'\n");
    printf("Wybrana opcja: ");

    char option;
    scanf("\n%c", &option);

    switch(option) {
        case 'm': {
            wprintf(L"Podaj liczbę wierzchołków: ");
            int n;
            scanf("%d", &n);
            GraphAdj graph(n);

            char** M = zeroMatrix(n, n);
            if(M == NULL) {
                wprintf(L"Alokacja pamięci nie powiodła się.\n");
                break;
            }
            wprintf(L"Aby zakończyć wczytywanie, jako krawędź należy podać '%d %d'\n", OFFSET-  1, OFFSET - 1);
            int i = 0;
            while(true) {
                wprintf(L"Podaj #%d krawędź (x y): ", ++i);
                int x1, x2;
                scanf("%d %d", &x1, &x2);
                //printf("%d %d\n", x1 - 1, x2 - 1);
                if(x1 == OFFSET -1 && x2 == OFFSET - 1)break;
                M[x1 - OFFSET][x2 - OFFSET] = 1;
                M[x2 - OFFSET][x1 - OFFSET] = 1;
                graph.AddEdge(x1 - OFFSET, x2 - OFFSET);
            }
            printMatrix(M, n, n);

            cycleAdjacencyMatrix(M, graph, n);
            break;
        }
        case 'g': {
            wprintf(L"Podaj liczbę wierzchołków: ");
            int n;
            scanf("%d", &n);

            char** M = zeroMatrix(n, n);
            if(M == NULL) {
                wprintf(L"Alokacja pamięci nie powiodła się.\n");
                break;
            }
            wprintf(L"Aby zakończyć wczytywanie, jako krawędź należy podać '%d %d'\n", OFFSET-  1, OFFSET - 1);
            int i = 0;
            while(true) {
                wprintf(L"Podaj #%d łuk (x y): ", ++i);
                int x1, x2;
                scanf("%d %d", &x1, &x2);
                if(x1 == OFFSET -1 && x2 == OFFSET - 1)break;
                M[x1 - OFFSET][x2 - OFFSET] = 1;
                M[x2 - OFFSET][x1 - OFFSET] = -1;
            }

            int** buf[3];
            if(matrixToLists(M, n, buf) == MEMORY_FAILURE) {
                deallocMatrix(M, n);
                wprintf(L"Alokacja pamięci nie powiodła się.\n");
                break;
            };

            int** grM = graphMatrixFrom(n, buf[0], buf[1], buf[2]);
            deallocMatrixInt(buf[0], n);
            deallocMatrixInt(buf[1], n);
            deallocMatrixInt(buf[2], n);
            deallocMatrix(M, n);
            if(grM == NULL) {
                wprintf(L"Alokacja pamięci nie powiodła się.\n");
                break;
            }

            printMatrixInt(grM, n, n + 4, 2, " ");

            cycleGraphMatrix(grM, n);

            deallocMatrixInt(grM, n);

            break;
        }
        default: 
            wprintf(L"Nieznana opcja, spróbuj ponownie.\n\n");
            break;
    }
}

void mainPresenting() {
    printf("cycle-seeker v1.0, tryb: prezentacja\n\n");
    wprintf(L"Wpisanie w dowolnym miejscu 'q' zakończy program.\n");
    wprintf(L"Natomiast wpisanie 'b' powróci do poprzedniego menu.\n\n");

    while(true) {
        wprintf(L"Wybierz co chcesz zrobić.\n");
        wprintf(L"Dla wczytania grafu z klawiatury, wpisz 'k'\n");
        wprintf(L"DLa wczytania grafu z pliku, wpisz 'f'\n");
        wprintf(L"Dla wyjścia, wpisz 'q'\n");
        printf("Wybrana opcja: ");

        char option;
        scanf("\n%c", &option);

        switch(option) {
            case 'q': exit(0);
            case 'k':
                nl();
                fromKeyboard();
                break;
            case 'f':
                nl();
                fromFile();
                break;
            case 'b': return;
        }
    }
}

void mainTesting() {
    // FILE* test = fopen("test.txt", "r");
    /* FILE* test = fopen("t", "r");
    int n, m;
    fscanf(test, "%d %d", &n, &m);

    char** M = zeroMatrix(n, n);
    int x1, x2;
    while(fscanf(test, "%d %d", &x1, &x2) == 2) {                    
        M[x1 - OFFSET][x2 - OFFSET] = 1;
        M[x2 - OFFSET][x1 - OFFSET] = -1;
    }
    printMatrix(M, n, n);

    int** buf[3];
    matrixToLists(M, n, buf);

    printList(buf[0], n, "->");
    nl();
    printList(buf[1], n, "->");
    nl();
    printList(buf[2], n, "->");

    int** grM = graphMatrixFrom(n, buf[0], buf[1], buf[2]);

    printMatrixInt(grM, n, n + 4, 2, " ");

    int* cycle = NULL;
    status_t hamiltonian = HamiltonianCycleM(grM, n, 1, &cycle);
    switch(hamiltonian) {
        case SUCCESS: {
            if(cycle != NULL) {
                wprintf(L"Cykl: ");
                printArrayInt(cycle, n + 1, " -> ");
                free(cycle);
            }
            break;
        }
        case FAILURE: {
            wprintf(L"Graf wejściowy nie zawiera cyklu.\n");
            break;
        }
        case MEMORY_FAILURE: {
            wprintf(L"Alokacja pamięci nie powiodła się.\n");
            break;
        }
    }

    deallocMatrixInt(grM, n);
    deallocMatrixInt(buf[0], n);
    deallocMatrixInt(buf[1], n);
    deallocMatrixInt(buf[2], n);
    deallocMatrix(M, n); */

    FILE* test = fopen("t1", "r");
    int n, m;
    fscanf(test, "%d %d", &n, &m);

    char** M = zeroMatrix(n, n);
    int x1, x2;
    while(fscanf(test, "%d %d", &x1, &x2) == 2) {                    
        M[x1 - OFFSET][x2 - OFFSET] = 1;
        M[x2 - OFFSET][x1 - OFFSET] = 1;
    }
    printMatrix(M, n, n);

    int* euler = NULL;

    status_t eulerianCircuit = EulerianCircuitA(M, n, m, 1, &euler);
    switch(eulerianCircuit) {
        case SUCCESS: {
            printf("Cykl: ");
            printArrayInt(euler, m + 1, " -> ");
            free(euler);
            break;
        }
        case FAILURE: {
            wprintf(L"Graf wejściowy nie zawiera cyklu.\n");
            break;
        }
        case MEMORY_FAILURE: {
            wprintf(L"Alokacja pamięci nie powiodła się.\n");
            break;
        }
    }

    return;
}

int main(int argc, char** argv) {
    system("chcp 65001 > nul");
    setlocale(LC_CTYPE, ".1250");

    printf("cycle-seeker v1.0\n\n");
    wprintf(L"W jaki tryb ma przejść program? (p)rezentacja, (t)estowanie: ");
    char mode = getchar();
    switch(mode) {
        case 'p':
            system("clear");
            mainPresenting();
            break;
        case 't':
            mainTesting();
            break;
    }
    return 0;
}