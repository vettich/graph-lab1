#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <graphbase.h>

class Graph
{
    GraphBase *graph;

public:
    Graph();
    ~Graph();

    void readGraph(std::string filename);
    void writeGraph(std::string filename);
    void addEdge(int from, int to, int weight=1);
    void removeEdge(int from, int to);
    int changeEdge(int from, int to, int newWeight=1);
    void transformToAdjList();
    void transformToAdjMatrix();
    void transformToListOfEdges();
};

#endif // GRAPH_H
