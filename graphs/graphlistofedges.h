#ifndef GRAPHLISTOFEDGES_H
#define GRAPHLISTOFEDGES_H

#include "graphbase.h"
#include <vector>
#include <tuple>

typedef std::unordered_multimap<int,std::pair<int,int>> Edges;

class GraphListOfEdges : public GraphBase
{
public:
    Edges data;
    bool is_directed;
    std::size_t NTops;

    GraphListOfEdges();
    GraphListOfEdges(const std::pair<SpainingTree,int> &set);
    virtual ~GraphListOfEdges();
    virtual void Fill(std::ifstream &in);
    virtual void Write(std::ostream &out);
    virtual void addEdge(int from,int to, int weight);
    virtual void removeEdge(int from,int to);
    virtual int changeEdge(int from,int to,int newWeight);
    virtual std::pair<SpainingTree,int> getSpainingTreePrima();
    std::pair<SpainingTree,int> getSpainingTreeKruscal();
    std::pair<SpainingTree,int> getSpainingTreeBoruvka();
    int CheckEuler(bool &circleExist);
    std::vector<int> getEuleranTourFleri();
    std::vector<int> getEuleranTourEffective();

private:
    void erase(int from,int to);
    void erase(Edges &d, int from,int to);
    int DFSCount (int v, std::vector<bool> &visited, const Edges &copy);
    bool isValidNextEdge(int u, int v,Edges &copy);
    void proc (int u,Edges &copy,std::vector<int> &R);
};

#endif // GRAPHLISTOFEDGES_H
