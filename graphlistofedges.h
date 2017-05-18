#ifndef GRAPHLISTOFEDGES_H
#define GRAPHLISTOFEDGES_H

#include "graphbase.h"
#include <vector>
#include <tuple>

class GraphListOfEdges : public GraphBase
{
public:
    int N; // количество вершин графа
    int M; // количество ребер графа
    int R; // ориентированность графа
    int W; // взвешенность графа
    std::vector <std::tuple<int,int,int> > graph;

    GraphListOfEdges():GraphBase() {}
//    GraphListOfEdges(std::string filename):GraphBase(filename) {}
//    GraphListOfEdges(std::ifstream& file):GraphBase(file) {}
    virtual ~GraphListOfEdges();
    virtual char type() {return 'E';}
    virtual void init();
    virtual void read(std::ifstream& file);
    virtual void write(std::ofstream& file);
    virtual void addEdge(int from, int to, int weight);
    virtual void removeEdge(int from, int to);
    virtual int changeEdge(int from, int to, int newWeight);

    virtual GraphBase *transformToAdjList();
    virtual GraphBase *transformToAdjMatrix();
};

#endif // GRAPHLISTOFEDGES_H
