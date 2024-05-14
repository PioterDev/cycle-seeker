#include <iostream>
#include <algorithm>
#include <list>
#include <string.h>
#include <vector>

struct GraphMat {
    int** mat;
    int size;
    GraphMat(int** mat, int num);
    void AddEdge(int v, int w);
    void PrintMat();
    int GetSize();
    bool IsConnected(int a, int b);
    ~GraphMat();

    void GenerateMat();

    void rmvEdge(int u, int v);

    void printEulerTour();
    void printEulerUtil(int s);

    int DFSCount(int v, bool visited[]);

    bool isValidNextEdge(int u, int v);

    bool containsEulersCircuit();
    bool isConnected();
    void DFSUtil(int v, bool visited[]);
    bool edgeExists(int i, int j);
    bool edgeExistsBothWays(int i, int j);
};
