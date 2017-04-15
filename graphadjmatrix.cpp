#include "graphadjmatrix.h"
#include <fstream>

GraphAdjMatrix::~GraphAdjMatrix()
{
    // nothing to destroy
}

void GraphAdjMatrix::init()
{
    W = 0;
    N = 0;
}

void GraphAdjMatrix::read(std::ifstream &file)
{
    file >> N >> W;
    graph.resize(N);
    for(int i=0; i<N; i++) {
        graph[i].resize(N);
        for(int j=0; j<N; j++) {
            file >> graph[i][j];
        }
    }
}

void GraphAdjMatrix::write(std::ofstream &file)
{
    file << N << ' ' << W << std::endl;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            file << graph[i][j] << ' ';
        }
        file << std::endl;
    }
}

void GraphAdjMatrix::addEdge(int from, int to, int weight)
{
    if(from >= N or to >= N)
        return;
    graph[from][to] = weight;
}

void GraphAdjMatrix::removeEdge(int from, int to)
{
    if(from >= N or to >= N)
        return;
    graph[from][to] = 0;
}

int GraphAdjMatrix::changeEdge(int from, int to, int newWeight)
{
    if(from >= N or to >= N)
        return 0;
    graph[from][to] = newWeight;
}
