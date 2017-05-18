#include "graphadjmatrix.h"
#include "graphadjlist.h"
#include "graphlistofedges.h"
#include <fstream>
#include <iostream>

using namespace std;

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
    file << N << endl;
    file << W << endl;
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
    int oldWeight = graph[from][to];
    graph[from][to] = newWeight;
    return oldWeight;
}

GraphBase *GraphAdjMatrix::transformToAdjList()
{
    GraphAdjList *g = new GraphAdjList();
    g->N = N;
    g->W = W;
    g->R = 0;
    for (int i = 0; i < N; ++i)
    {
        vector<pair<int,int>> temp2;
        for (int j = 0; j < N; ++j)
        {
            if(graph[i][j] != 0)
            {
                temp2.push_back(make_pair(j+1,graph[i][j]));
            }
        }
        g->graph.push_back(temp2);
    }
    return g;
}

GraphBase *GraphAdjMatrix::transformToListOfEdges()
{
    GraphListOfEdges *g = new GraphListOfEdges();
    g->N = N;
    g->W = W;
    g->R = 0;
    g->M = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if(graph[i][j]) {
                if(!W) {
                    g->graph.push_back(make_tuple(i+1,j+1, 1));
                    g->M++;
                } else {
                    g->graph.push_back(make_tuple(i+1,j+1, graph[i][j]));
                    g->M++;
                }
            }
        }
    }
    return g;
}
