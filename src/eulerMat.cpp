#include "../include/eulerMat.h"

GraphMat::GraphMat(int** mat, int num) : mat(mat), size(num)
{
}

void GraphMat::AddEdge(int v, int w)
{
}

GraphMat::~GraphMat()
{
}

bool GraphMat::edgeExists(int i, int j)
{
    // return  (mat[i][j] >= 0 && mat[i][j] <= size) ||
    //         (mat[i][j] >= 2 * size + 1 && mat[i][j] <= 3 * size);
    return mat[i][j] >= 0 && mat[i][j] <= size;
}

bool GraphMat::edgeExistsBothWays(int i, int j)
{
    return (mat[i][j] >= 2 * size + 1 && mat[i][j] <= 3 * size);
}

void GraphMat::DFSUtil(int v, bool visited[])
{
    visited[v] = true;
 
    for (int i = 0; i < size; i++)
    {
        if (visited[i])
            continue;
        if (edgeExists(v, i))
            DFSUtil(i, visited);
    }
}

// Sprawdza czy wszystkie nie zerowe wierzcholki sa polaczone
bool GraphMat::containsEulersCircuit()
{
    bool* visited = new bool[size];

    for (int i = 0; i < size; i++)
        visited[i] = false;

    // Znajdywanie pierwszego nizerowego wierzcholka
    int nonZero = size;
    for (int i = 0; i < size; i++)
    {
        int inCount = 0;
        int outCount = 0;
        for (int j = 0; j < size; j++)
        {
            std::cout << i << " " << j << std::endl;
            if (edgeExists(i, j))
            {
                std::cout << "out\n";
                if (!edgeExistsBothWays(i, j))
                    outCount++;
                if (nonZero == size)
                    nonZero = i;
            }

            if (edgeExists(j, i))
            {
                std::cout << "in\n";
                if (!edgeExistsBothWays(i, j))
                    inCount++;
            }
        }

        std::cout << "in: " << inCount << ", out: " << outCount << std::endl;
        if (inCount != outCount)
            return false;
    }

    // Jezeli nie ma krawedzi w grafie to zwracamy prawde
    if (nonZero == size)
        return true;

    // DFS
    DFSUtil(nonZero, visited);

    // Sprawdzamy czy wszystkie niezerowe wierzcholki zostaly odwiedzone
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (edgeExists(i, j) && !visited[i])
                return false;

    delete[] visited;
    return true;
}

void GraphMat::printEulerTour()
{
    // Sprawdzenie czy graf zawiera cylk eulera
    if (!containsEulersCircuit())
    {
        std::cout << "Graf nie zawiera cyklu eulera" << std::endl;
        return;
    }

    // Szukanie wierzcholka o nieparzystym stopniu, a jak nie ma to zerowy dajemy
    int u = 0;
    for (int i = 0; i < size; i++)
    {
        int connectionCount = 0;
        for (int j = 0; j < size; j++)
        {
            if (edgeExists(i, j))
                connectionCount++;
        }

        if (connectionCount % 2 == 1)
        {
            u = i;
            break;
        }
    }

    printEulerUtil(u);
    std::cout << std::endl;
}

void GraphMat::printEulerUtil(int u)
{
    // Wykonaj dla wszystkich wierzcholkow sasiadujacych
    for (int i = 0; i < size; i++)
    {
        if (!edgeExists(u, i))
            continue;

        // Sprawdzamy czy krawedz nie zostla usunieta i czy powinna zostac wybrana ponad inne
        if (isValidNextEdge(u, i))
        {
            std::cout << u << "  ";
            mat[u][i] = -2 * size;
            printEulerUtil(i);
        }
    }
}

// The function to check if edge u-v can be considered as
// next edge in Euler Tout
bool GraphMat::isValidNextEdge(int u, int v)
{
    // Wybieramy go jeżeli jest jedynym wierzcholkiem
    int connectionCount = 0;
    for (int i = 0; i < size; i++)
        if (edgeExists(u, i))
            connectionCount++;
    if (connectionCount == 1)
        return true;

    // Jezeli jest ich kilka to sprawdzamy czy jest mostem
    
    // Liczba wierzcholkow do ktorych sie da dotrzec przed usunieciem krawedzi
    bool* visited = new bool[size];
    memset(visited, false, size);
    int count1 = DFSCount(u, visited);

    // i po jej usunieciu
    int val = mat[u][v];
    mat[u][v] = -2 * size;
    memset(visited, false, size);
    int count2 = DFSCount(u, visited);

    mat[u][v] = val;
    delete[] visited;

    return (count1 > count2) ? false : true;
}

// Funkcja liczy ilosc wierzcholkow do ktorych da sie dotrzec z danego wierzcholka
int GraphMat::DFSCount(int v, bool visited[])
{
    visited[v] = true;
    int count = 1;

    int connectionCount = 0;
    for (int i = 0; i < size; i++)
        if (edgeExists(v, i) && !visited[i])
            count += DFSCount(i, visited);

    return count;
}
