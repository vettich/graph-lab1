#ifndef GRAPHBASE_H
#define GRAPHBASE_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <tuple>
#include <set>
#include "dsu.h"

typedef std::tuple<int,int,int> EdgeTuple;
typedef std::vector<EdgeTuple> SpainingTree;


class GraphBase
{
public:
    GraphBase (char pt);
    virtual ~GraphBase () {}
    virtual void Fill(std::ifstream &in) =0;
    virtual void addEdge(int from,int to, int weight) =0;
    virtual void removeEdge(int from,int to) =0;
    virtual int changeEdge(int from,int to,int newWeight)=0;
    virtual void Write(std::ostream &out) =0;
    virtual std::pair<SpainingTree,int> getSpainingTreePrima() =0;
    virtual std::pair<SpainingTree,int> getSpainingTreeKruscal() =0;
    virtual std::pair<SpainingTree,int> getSpainingTreeBoruvka() =0;
    virtual int CheckEuler(bool &circleExist) =0;
    virtual std::vector<int> getEuleranTourEffective() =0;
    virtual std::vector<int> getEuleranTourFleri() =0;
    void print();

    bool is_weighted;
    bool is_directed;
    char type;
};

#endif // GRAPHBASE_H
