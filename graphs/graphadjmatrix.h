#ifndef GRAPHADJMATRIX_H
#define GRAPHADJMATRIX_H

#include <vector>
#include "graphbase.h"

typedef std::vector<int> IntVec;
typedef std::vector<IntVec> Matrix;

class GraphAdjMatrix : public GraphBase
{
public:
    Matrix data;

    GraphAdjMatrix();
    virtual ~GraphAdjMatrix() {}
    virtual void Fill(std::ifstream &in);
    virtual void Write(std::ostream &out);
    virtual void addEdge(int from,int to, int weight);
    virtual void removeEdge(int from,int to);
    virtual int changeEdge(int from,int to,int newWeight);
    virtual std::pair<SpainingTree,int> getSpainingTreePrima();
    virtual std::pair<SpainingTree,int> getSpainingTreeKruscal();
    virtual std::pair<SpainingTree,int> getSpainingTreeBoruvka();
    int CheckEuler(bool &circleExist);
    std::vector<int> getEuleranTourFleri();
    std::vector<int> getEuleranTourEffective();
private:
    int DFSCount (int v, std::vector<bool> &visited, const Matrix &copy);
    bool isValidNextEdge(int u, int v,Matrix &copy);
    void proc (int u,Matrix &copy,std::vector<int> &R);

};

#endif // GRAPHADJMATRIX_H
