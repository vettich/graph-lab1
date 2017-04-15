#ifndef GRAPHLISTOFEDGES_H
#define GRAPHLISTOFEDGES_H

#include "graphbase.h"

class GraphListOfEdges : public GraphBase
{
public:
    GraphListOfEdges();
    ~GraphListOfEdges();
    virtual void read(std::string filename);
    virtual void write(std::string filename);
    virtual void addEdge(int from, int to, int weight);
    virtual void removeEdge(int from, int to);
    virtual int changeEdge(int from, int to, int newWeight);
};

#endif // GRAPHLISTOFEDGES_H
