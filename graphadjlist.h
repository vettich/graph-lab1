#ifndef GRAPHADJLIST_H
#define GRAPHADJLIST_H

#include "graphbase.h"
#include <vector>
#include <tuple>
#include <set>

class GraphAdjList : public GraphBase
{
    int N; // количество вершин графа
    bool R; // ориентированность графа
    bool W; // взвешенность графа
//    std::vector< std::set< std::tuple<int, int, int> > > graph_w;
//    std::vector< std::set< std::pair<int, int> > > graph;
    std::vector< std::tuple<int, int, int> > graph;
public:
    GraphAdjList():GraphBase() {}
    GraphAdjList(std::string filename):GraphBase(filename){}
    GraphAdjList(std::ifstream &file):GraphBase(file){}
    ~GraphAdjList();
    virtual void init();
    virtual void read(std::ifstream& file);
    virtual void write(std::ifstream file);
    virtual void addEdge(int from, int to, int weight);
    virtual void removeEdge(int from, int to);
    virtual int changeEdge(int from, int to, int newWeight);
};

#endif // GRAPHADJLIST_H
