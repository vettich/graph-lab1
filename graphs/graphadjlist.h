#ifndef GRAPHADJLIST_H
#define GRAPHADJLIST_H

#include "graphbase.h"
#include <vector>
#include <tuple>
#include <set>

typedef std::unordered_map<int,int> List;
typedef std::vector<List> Lists;

class GraphAdjList : public GraphBase
{
public:
    Lists data;

    GraphAdjList();
    virtual ~GraphAdjList() {}
    virtual void Fill(std::ifstream &in);
    virtual void Write(std::ostream &out);
    virtual void addEdge(int from,int to, int weight);
    virtual void removeEdge(int from,int to);
    virtual int changeEdge(int from,int to,int newWeight);
    virtual std::pair<SpainingTree,int> getSpainingTreePrima();
    virtual std::pair<SpainingTree,int> getSpainingTreeKruscal();
    virtual std::pair<SpainingTree,int> getSpainingTreeBoruvka();
    int CheckEuler(bool &circleExist);
    std::vector<int> getEuleranTourEffective();
    std::vector<int> getEuleranTourFleri();

private:
    int DFSCount (int v, std::vector<bool> &visited, const Lists &copy);
    bool isValidNextEdge(int u, int v,Lists &copy);
    void proc (int u,Lists &copy,std::vector<int> &R);
};

#endif // GRAPHADJLIST_H
