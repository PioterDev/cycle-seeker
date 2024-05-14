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
    return  (mat[i][j] >= 0 && mat[i][j] <= size) ||
            (mat[i][j] >= 2 * size + 1 && mat[i][j] <= 3 * size);
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
bool GraphMat::isConnected()
{
    bool* visited = new bool[size];

    for (int i = 0; i < size; i++)
        visited[i] = false;

    // Znajdywanie pierwszego nizerowego wierzcholka
    int nonZero = size;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (edgeExists(i, j))
            {
                nonZero = i;
                break;
            }
        }
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

bool GraphMat::containsEulersCircuit()
{
    if (isConnected() == false)
        return 0;

    // Liczymy nieparzyste
    int odd = 0;
    for (int i = 0; i < size; i++)
    {
        int count = 0;
        for (int j = 0; j < size; j++)
        {
            if (edgeExists(i, j))
                count++;
        }
        if (count % 2 == 1)
            odd++;
    }

    return (odd == 0);
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
        if (adj[u][i] != -1 && isValidNextEdge(u, i))
        {
            std::cout << u << "  ";
            rmvEdge(u, i);
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
    rmvEdge(u, v);
    memset(visited, false, size);
    int count2 = DFSCount(u, visited);

    AddEdge(u, v);
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
