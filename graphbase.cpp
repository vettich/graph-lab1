#include "graphbase.h"
#include <fstream>

GraphBase::GraphBase()
{
    init();
}

GraphBase::GraphBase(std::string filename)
{
    read(filename);
    init();
}

GraphBase::GraphBase(std::ifstream &file)
{
    read(file);
    init();
}

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

void GraphBase::read(std::ifstream &file)
{
    // do nothing
}

void GraphBase::write(std::string filename)
{
    std::ofstream file(filename.data());
    write(file);
    file.close();
}

void GraphBase::write(std::ofstream &file)
{
    // do nothing
}

void GraphBase::addEdge(int from, int to, int weight)
{
    // do nothing
}

void GraphBase::removeEdge(int from, int to)
{
    // do nothing
}

int GraphBase::changeEdge(int from, int to, int newWeight)
{
    // do nothing, of course
}

