#include "graph.h"

#include <iostream>
#include <fstream>
#include "graphadjlist.h"
#include "graphadjmatrix.h"
#include "graphlistofedges.h"

Graph::Graph()
{
    graph = NULL;
}

Graph::~Graph()
{
    delete graph;
}

std::string Graph::type()
{
    if(graph) switch(graph->type()) {
    case 'C': return "матрица смежности";
    case 'L': return "список смежности";
    case 'E': return "список ребер";
    }
    return "неизвестно";
}

char Graph::typeChar()
{
    if(graph) return graph->type();
    return '~';
}

bool Graph::readGraph(std::string filename)
{
    if(graph) delete graph;
    graph = GraphBase::create(filename);
    return !!graph;
}

bool Graph::writeGraph(std::string filename)
{
    if(!graph) return false;
    graph->write(filename);
    return true;
}

void Graph::addEdge(int from, int to, int weight)
{
    if(!graph) return;
    graph->addEdge(from, to, weight);
}

void Graph::removeEdge(int from, int to)
{
    if(!graph) return;
    graph->removeEdge(from, to);
}

int Graph::changeEdge(int from, int to, int newWeight)
{
    if(!graph) return 0;
    return graph->changeEdge(from, to, newWeight);
}

void Graph::transformToAdjList()
{
    if(!graph) return;
    GraphBase *new_graph = graph->transformToAdjList();
    if(new_graph != graph) {
        delete graph;
        graph = new_graph;
    }
}

void Graph::transformToAdjMatrix()
{
    if(!graph) return;
    GraphBase *new_graph = graph->transformToAdjMatrix();
    if(new_graph != graph) {
        delete graph;
        graph = new_graph;
    }
}

void Graph::transformToListOfEdges()
{
    if(!graph) return;
    GraphBase *new_graph = graph->transformToListOfEdges();
    if(new_graph != graph) {
        delete graph;
        graph = new_graph;
    }
}

