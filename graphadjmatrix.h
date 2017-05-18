#ifndef GRAPHADJMATRIX_H
#define GRAPHADJMATRIX_H

#include <vector>
#include "graphbase.h"

class GraphAdjMatrix : public GraphBase
{
public:
    int N; // количество вершин графа
    bool W; // вес графа
    std::vector< std::vector<int> > graph; // граф

    GraphAdjMatrix():GraphBase() {}
//    GraphAdjMatrix(std::string filename):GraphBase(filename) {}
//    GraphAdjMatrix(std::ifstream& file):GraphBase(file) {}
    virtual ~GraphAdjMatrix();
    virtual char type() {return 'C';}
    virtual void init();
    virtual void read(std::ifstream& file);
    virtual void write(std::ofstream& file);
    virtual void addEdge(int from, int to, int weight);
    virtual void removeEdge(int from, int to);
    virtual int changeEdge(int from, int to, int newWeight);

    virtual GraphBase *transformToAdjList();
    virtual GraphBase *transformToListOfEdges();
};

#endif // GRAPHADJMATRIX_H
