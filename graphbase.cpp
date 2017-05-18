#include "graphbase.h"
#include <iostream>
#include <fstream>
#include "graphadjlist.h"
#include "graphadjmatrix.h"
#include "graphlistofedges.h"

using namespace std;

GraphBase::GraphBase()
{
    init();
}

//GraphBase::GraphBase(std::string filename)
//{
//    init();
////    read(filename);
//}

//GraphBase::GraphBase(std::ifstream &file)
//{
//    init();
////    read(file);
//}

GraphBase::~GraphBase()
{
    // destroy anything
}

void GraphBase::init()
{
    // init
}

void GraphBase::read(std::string filename)
{
    std::ifstream file(filename.data());
    read(file);
    file.close();
}

void GraphBase::read(std::ifstream &)
{
    // do nothing ...
}

void GraphBase::write(std::string filename)
{
    std::ofstream file(filename.data());
    file << type() << endl;
    write(file);
    file.close();
}

GraphBase *GraphBase::create(std::string filename)
{
    std::ifstream f(filename.data());
    if(!f.good()) return NULL;
    char byte;
    f >> byte;
    GraphBase *graph = NULL;
    if(byte == 'C') {
        graph = new GraphAdjMatrix();
    } else if(byte == 'L') {
        graph = new GraphAdjList();
    } else if(byte == 'E') {
        graph = new GraphListOfEdges();
    } else {
        return NULL;
    }
    graph->read(f);
    f.close();
    return graph;
}

void GraphBase::write(std::ofstream &)
{
    // do nothing
}

void GraphBase::addEdge(int , int , int )
{
    // do nothing
}

void GraphBase::removeEdge(int , int )
{
    // do nothing
}

int GraphBase::changeEdge(int , int , int )
{
    // do nothing, of course
    return 0;
}

GraphBase *GraphBase::transformToAdjList()
{
    return this;
}

GraphBase *GraphBase::transformToAdjMatrix()
{
    return this;
}

GraphBase *GraphBase::transformToListOfEdges()
{
    return this;
}

