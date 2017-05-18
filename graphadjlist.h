#ifndef GRAPHADJLIST_H
#define GRAPHADJLIST_H

#include "graphbase.h"
#include <vector>
#include <tuple>
#include <set>

class GraphAdjList : public GraphBase
{
public:
    int N; // количество вершин графа
    bool R; // ориентированность графа
    bool W; // взвешенность графа
    std::vector<std::vector<std::pair <int,int>> > graph;

    GraphAdjList():GraphBase() {}
//    GraphAdjList(std::string filename):GraphBase(filename){}
//    GraphAdjList(std::ifstream &file):GraphBase(file){}
    ~GraphAdjList();
    virtual char type() {return 'L';}
    virtual void init();
    virtual void read(std::ifstream& file);
    virtual void write(std::ofstream &file);
    virtual void addEdge(int from, int to, int weight);
    virtual void removeEdge(int from, int to);
    virtual int changeEdge(int from, int to, int newWeight);

    virtual GraphBase *transformToAdjMatrix();
    virtual GraphBase *transformToListOfEdges();
};

#endif // GRAPHADJLIST_H
