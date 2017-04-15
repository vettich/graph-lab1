#include "graph.h"

#include <iostream>
#include <fstream>
#include "graphadjlist.h"
#include "graphadjmatrix.h"
#include "graphlistofedges.h"

Graph::Graph()
{

}

Graph::~Graph()
{

}

void Graph::readGraph(std::string filename)
{
    std::ifstream f(filename.data());
    char byte;
    f >> byte;
    f.close();
    if(byte == 'C') {
        delete graph;
        graph = new GraphAdjMatrix(f);
    }
}

void Graph::writeGraph(std::string filename)
{

}

void Graph::addEdge(int from, int to, int weight)
{

}

void Graph::removeEdge(int from, int to)
{

}

int Graph::changeEdge(int from, int to, int newWeight)
{

}

void Graph::transformToAdjList()
{

}

void Graph::transformToAdjMatrix()
{

}

void Graph::transformToListOfEdges()
{

}

