#include "graphadjlist.h"
#include <fstream>

GraphAdjList::~GraphAdjList()
{

}

void GraphAdjList::init()
{
    N = 0;
    R = 0;
    W = 0;
}


void GraphAdjList::read(std::ifstream &file)
{
    file >> N >> R >> W;
    for(int i=0; i<N; i++) {
        int from, to, weight;
        file >> from >> to;
        if(W) {
            file >> weight;
        } else {
            weight = 1;
        }
        graph.push_back(std::make_tuple(from, to, weight));
        if(R) {
            graph.push_back(std::make_tuple(to, from, weight));
        }
    }
}

void GraphAdjList::write(std::ifstream file)
{
    file << N << R;
}

void GraphAdjList::addEdge(int from, int to, int weight)
{
    graph.push_back(std::make_tuple(from, to, weight));
    N++;
}

void GraphAdjList::removeEdge(int from, int to)
{
    for(int i=0; i<N; i++) {
        std::tuple v = graph[i];
        if(std::get<0>(v) == from && std::get<1>(v) == to) {

        }
    }
    N--;
}

int GraphAdjList::changeEdge(int from, int to, int newWeight)
{

}
