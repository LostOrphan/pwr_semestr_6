#pragma once
#include <string>
#include "customStructures.h"
constexpr int INF = 2147483647;

class Graph
{
private:
    int **matrix = nullptr;
    int N;
    // Zmienne do RNN
    int globalMinCostRNN = INF;
    int *globalBestPathRNN = nullptr;
    int globalStartNode = -1;

public:
    Graph(int cities);
    ~Graph();

    void setEdge(int from, int to, int weight);
    int getEdge(int from, int to) const;
    void getGraphfromFile(const std::string &filename);
    void generateRandomGraph(int cities, int minWeight, int maxWeight);
    void printGraph();
    void swapElements(int &a, int &b);
    void reverseArray(int *arr, int start, int end);
    bool generateNextPermutation(int *arr, int size);
    void shuffleArray(int *arr, int size);
    int getN() const;
    AlgorithmResult runNN(const Graph &g, int startNode = 0);
    void exploreNN(const Graph &g, int currentNode, int startNode, bool *visited,
                   int *currentPath, int step, int currentCost,
                   int &bestCost, int *bestPath); 

    int calculateBound(const Node& node,const Graph& g);
    AlgorithmResult runBnB_BFS(const Graph &g);
    AlgorithmResult runBnB_BestFS(const Graph& g);
};