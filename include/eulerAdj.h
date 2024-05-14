#include <iostream>
#include <algorithm>
#include <list>
#include <string.h>

struct GraphAdj {
    int** adj;
    int size;
    GraphAdj(int num);
    void AddEdge(int v, int w);
    void PrintAdj();
    ~GraphAdj();

    void rmvEdge(int u, int v);

    void printEulerTour();
    void printEulerUtil(int s);

    int DFSCount(int v, bool visited[]);

    bool isValidNextEdge(int u, int v);

    bool containsEulersCircuit();
    bool isConnected();
    void DFSUtil(int v, bool visited[]);
};
