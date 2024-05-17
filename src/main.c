#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <time.h>

#include "euler.h"
#include "hamilton.h"
#include "rng.h"
#include "structs_unions_defines.h"
#include "tester.h"
#include "utils.h"

#define nl() printf("\n") //Prints a new line

void cycleAdjacencyMatrix(char** matrix, int n, int m) {
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
                        printArrayInt(cycle, n + 1, " -> ", stdout);
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
            int* cycle = NULL;
            status_t euler = EulerianCircuitA(matrix, n, m, 1, &cycle);

            switch(euler) {
                case MEMORY_FAILURE: {
                    wprintf(L"Alokacja pamięci nie powiodła się.\n");
                    break;
                }
                case FAILURE: {
                    wprintf(L"Graf wejściowy nie zawiera cyklu.\n");
                    break;
                }
                case SUCCESS: {
                    if(cycle != NULL) {
                        printf("Cykl: ");
                        printArrayInt(cycle, m + 1, " -> ", stdout);
                        free(cycle);
                    }
                    break;
                }
            }
            break;
        }
    }
}

void cycleGraphMatrix(int** matrix, int n, int m) {
    wprintf(L"Wybierz poszukiwany cykl.\n\n");
    wprintf(L"Dla Hamiltona, wpisz 'h'\n");
    wprintf(L"Dla Eulera, wpisz 'e'\n");
    printf("Wybrana opcja: ");

    char option;
    scanf("\n%c", &option);

    switch(option) {
        case 'h': {
            int* cycle = NULL;
            status_t hamiltonianCycle = HamiltonianCycleM(matrix, n, 1, &cycle, NULL);
            switch(hamiltonianCycle) {
                case SUCCESS: {
                    if(cycle != NULL) {
                        wprintf(L"Cykl: ");
                        printArrayInt(cycle, n + 1, " -> ", stdout);
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
            int* cycle = NULL;
            status_t euler = EulerianCircuitM(matrix, n, m, 1, &cycle);

            switch(euler) {
                case FAILURE: {
                    wprintf(L"Graf wejściowy nie zawiera cyklu.\n");
                    break;
                }
                case SUCCESS: {
                    if(cycle != NULL) {
                        printf("Cykl: ");
                        printArrayInt(cycle, m + 1, " -> ", stdout);
                        free(cycle);
                    }
                    break;
                }
                case MEMORY_FAILURE: {
                    wprintf(L"Alokacja pamięci nie powiodła się.\n");
                    break;
                }
            }
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
                char** M = zeroMatrix(vertices, vertices);
                if(M == NULL) {
                    wprintf(L"Alokacja pamięci nie powiodła się.\n");
                    break;
                }

                int x1, x2;
                while(fscanf(file, "%d %d", &x1, &x2) == 2) {                    
                    M[x1 - OFFSET][x2 - OFFSET] = 1;
                    M[x2 - OFFSET][x1 - OFFSET] = 1;
                }
                printMatrix(M, vertices, vertices, stdout);

                cycleAdjacencyMatrix(M, vertices, edges);

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
                // printMatrix(M, vertices, vertices);

                int** buf[4];
                if(matrixToLists(M, vertices, buf) == MEMORY_FAILURE) {
                    deallocMatrix(M, vertices);
                    wprintf(L"Alokacja pamięci nie powiodła się.\n");
                    break;
                };

                int** grM = graphMatrixFrom(vertices, buf[0], buf[1], buf[2], buf[3]);
                deallocMatrixInt(buf[0], vertices);
                deallocMatrixInt(buf[1], vertices);
                deallocMatrixInt(buf[2], vertices);
                deallocMatrixInt(buf[3], vertices);
                deallocMatrix(M, vertices);
                if(grM == NULL) {
                    wprintf(L"Alokacja pamięci nie powiodła się.\n");
                    break;
                }

                printMatrixInt(grM, vertices, vertices + 4, 2, " ", stdout);

                cycleGraphMatrix(grM, vertices, edges);

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

            wprintf(L"Podaj liczbę krawędzi: ");
            int m;
            scanf("%d", &m);

            char** M = zeroMatrix(n, n);
            if(M == NULL) {
                wprintf(L"Alokacja pamięci nie powiodła się.\n");
                break;
            }

            for(int i = 0; i < m; i++) {
                wprintf(L"Podaj #%d krawędź (x y): ", i + 1);
                int x1, x2;
                scanf("%d %d", &x1, &x2);
                M[x1 - OFFSET][x2 - OFFSET] = 1;
                M[x2 - OFFSET][x1 - OFFSET] = 1;
            }

            printMatrix(M, n, n, stdout);

            cycleAdjacencyMatrix(M, n, m);

            deallocMatrix(M, n);

            break;
        }
        case 'g': {
            wprintf(L"Podaj liczbę wierzchołków: ");
            int n;
            scanf("%d", &n);

            wprintf(L"Podaj liczbę krawędzi: ");
            int m;
            scanf("%d", &m);

            char** M = zeroMatrix(n, n);
            if(M == NULL) {
                wprintf(L"Alokacja pamięci nie powiodła się.\n");
                break;
            }

            for(int i = 0; i < m; i++) {
                wprintf(L"Podaj #%d łuk (x y): ", i + 1);
                int x1, x2;
                scanf("%d %d", &x1, &x2);
                M[x1 - OFFSET][x2 - OFFSET] = 1;
                M[x2 - OFFSET][x1 - OFFSET] = -1;
            }

            int** buf[4];
            if(matrixToLists(M, n, buf) == MEMORY_FAILURE) {
                deallocMatrix(M, n);
                wprintf(L"Alokacja pamięci nie powiodła się.\n");
                break;
            };

            int** grM = graphMatrixFrom(n, buf[0], buf[1], buf[2], buf[3]);
            deallocMatrixInt(buf[0], n);
            deallocMatrixInt(buf[1], n);
            deallocMatrixInt(buf[2], n);
            deallocMatrixInt(buf[3], n);
            deallocMatrix(M, n);
            if(grM == NULL) {
                wprintf(L"Alokacja pamięci nie powiodła się.\n");
                break;
            }

            printMatrixInt(grM, n, n + 4, 2, " ", stdout);

            cycleGraphMatrix(grM, n, m);

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
    FILE* testF = fopen("./tests.csv", "a");
    FILE* debugF = fopen("./debug.log", "w");
    // FILE* debugF = stdout;
    int n = 3100;
    while(n <= 10000) {
        printf("n: %d\n", n);
        for(int i = 0; i < 5; i++) {
            int* S = sequence(n);
            int* P = permute(S, n);
            free(S);
            fprintf(debugF, "Iteracja #%d: ", i + 1);
            for(int j = 0; j < 9; j++) {
                printArrayInt(P, n, " -> ", debugF);
                fprintf(debugF, "%d%% ", 10 * j + 10);
                char** M = zeroMatrix(n, n);
                
                genHamiltonianD(M, n, 10 * j + 10, P);

                /* int** buf[4];
                matrixToLists(M, n, buf); */

                // int** grM = graphMatrixFrom(n, buf[0], buf[1], buf[2], buf[3]);
                
                /* deallocMatrixInt(buf[0], n);
                deallocMatrixInt(buf[1], n);
                deallocMatrixInt(buf[2], n);
                deallocMatrixInt(buf[3], n); */

                // printMatrix(M, n, n, debugF);
                // printMatrixInt(grM, n, n + 4, 3, " ", debugF);

                fprintf(testF, "H;%d;%d;%lld\n", n, 10 * j + 10, test('h', M, NULL, n, debugF)/* , test('h', NULL, grM, n, NULL) */);

                deallocMatrix(M, n);
                // deallocMatrixInt(grM, n);
            }
            fprintf(debugF, "\n");
            free(P);
        }

        n += 100;
    }
    fclose(testF);
}

int main() {
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