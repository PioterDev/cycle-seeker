#include "../include/eulerAdj.h"

GraphAdj::GraphAdj(int size) : size(size)
{
    adj = new int*[size];
    for (int i = 0; i < size; i++)
    {
        adj[i] = new int[size];
        for (int j = 0; j < size; j++)
            adj[i][j] = false;
    }
}

GraphAdj::~GraphAdj()
{
    for (int i = 0; i < size; i++)
        delete[] adj[i];
    delete[] adj;
}

void GraphAdj::PrintAdj()
{
    for (int i = 0; i < this->size; i++)
    {
        for (int j = 0; j < this->size; j++)
            std::cout << adj[i][j] << " ";
        std::cout << "\n";
    }
}

void GraphAdj::AddEdge(int v, int w)
{
    adj[v][w] = 1;
    adj[w][v] = 1;
}

void GraphAdj::DFSUtil(int v, bool visited[])
{
    visited[v] = true;
 
    for (int i = 0; i < size; i++)
    {
        if (adj[v][i] == 1 && !visited[i])
            DFSUtil(i, visited);
    }
}

// Sprawdza czy wszystkie nie zerowe wierzcholki sa polaczone
bool GraphAdj::isConnected()
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
            if (adj[i][j] == 1)
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
            if (adj[i][j] == 1 && !visited[i])
                return false;

    delete[] visited;
    return true;
}

bool GraphAdj::containsEulersCircuit()
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
            if (adj[i][j] == 1)
                count++;
        }
        if (count % 2 == 1)
            odd++;
    }

    return (odd == 0);
}

void GraphAdj::printEulerTour()
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
            if (adj[i][j] == 1)
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

void GraphAdj::printEulerUtil(int u)
{
    // Wykonaj dla wszystkich wierzcholkow sasiadujacych
    for (int i = 0; i < size; i++)
    {
        if (adj[u][i] != 1)
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
bool GraphAdj::isValidNextEdge(int u, int v)
{
    // Wybieramy go jeżeli jest jedynym wierzcholkiem
    int connectionCount = 0;
    for (int i = 0; i < size; i++)
        if (adj[u][i] == 1)
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

// Usuniecie krawedzi (zamiana z 1 na -1)
void GraphAdj::rmvEdge(int u, int v)
{
    adj[u][v] = -1;
    adj[v][u] = -1;
}

// Funkcja liczy ilosc wierzcholkow do ktorych da sie dotrzec z danego wierzcholka
int GraphAdj::DFSCount(int v, bool visited[])
{
    visited[v] = true;
    int count = 1;

    int connectionCount = 0;
    for (int i = 0; i < size; i++)
        if (adj[v][i] == 1 && !visited[i])
            count += DFSCount(i, visited);

    return count;
}
