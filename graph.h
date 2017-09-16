#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <graphs/graphbase.h>
#include <c++/7.1.1/type_traits>

class Graph
{
public:
    Graph();
    ~Graph();
    void readGraph(std::string fileName);
    void addEdge(int from,int to, int weight);
    void removeEdge(int from,int to);
    int changeEdge(int from,int to,int newWeight);
    void transformToAdjList();
    void transformToAdjMatrix();
    void transformToListOfEdges();
    void writeGraph(std::string fileName);

    Graph getSpainingTreePrima() const;
    Graph getSpainingTreeKruscal() const;

    Graph getSpainingTreeBoruvka() const;
    int CheckEuler(bool &circleExist);
    std::vector<int> getEuleranTourFleri();
    std::vector<int> getEuleranTourEffective();

    char type();
    bool isGraph();
    void print();
private:
    GraphBase* data;

};


#endif // GRAPH_H
