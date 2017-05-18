#include "graphlistofedges.h"
#include "graphadjlist.h"
#include "graphadjmatrix.h"
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>

using namespace std;

GraphListOfEdges::~GraphListOfEdges()
{

}

void GraphListOfEdges::init()
{

}

void GraphListOfEdges::read(std::ifstream &file)
{
    file >> N >> M >> R >> W;
    graph.reserve(M);
    for (int i = 0; i < M; ++i) {
        if(W == 0) {
            int t1,t2;
            file >> t1 >> t2;
            graph.push_back(make_tuple(t1,t2,1));
        } else {
            int t1,t2,t3;
            file >> t1 >> t2 >> t3;
            graph.push_back( make_tuple(t1,t2,t3));
        }
    }
}

void GraphListOfEdges::write(std::ofstream &file)
{
    file << N << endl;
    file << M << endl;
    file << R << endl;
    file << W << endl;
    if(W == 0) {
        for(size_t i = 0; i < graph.size(); i++) {
            file << get<0>(graph[i]) << ' '
                 << get<1>(graph[i]) << endl;
        }
    } else {
        for(size_t i = 0; i < graph.size(); i++) {
            file << get<0>(graph[i]) << ' '
                 << get<1>(graph[i]) << ' '
                 << get<2>(graph[i]) << endl;
        }
    }
}

void GraphListOfEdges::addEdge(int from, int to, int weight)
{
    if(W == 0) {
        graph.push_back(make_tuple(from,to, 1));
    } else {
        graph.push_back(make_tuple(from,to,weight));
    }
}

void GraphListOfEdges::removeEdge(int from, int to)
{
    for(int i = 0; i < N; i++){
        if((from == get<0>(graph[i]) && to == get<1>(graph[i]))
            || (from == get<1>(graph[i]) && to == get<0>(graph[i]))) {
            graph.erase(graph.begin() + i );
        }
    }
}

int GraphListOfEdges::changeEdge(int from, int to, int newWeight)
{
    int oldWeight;
    for (size_t i = 0; i < graph.size(); ++i) {
        if((get<0>(graph[i]) == from && get<1>(graph[i]) == to )
            || (get<0>(graph[i]) == to && get<1>(graph[i]) == from )) {
            oldWeight = get<2>(graph[i]);
            get<2>(graph[i]) = newWeight;
        }
    }
    return oldWeight;
}

GraphBase *GraphListOfEdges::transformToAdjList()
{
    GraphAdjList *g = new GraphAdjList();
    g->N = N;
    g->W = W;
    g->R = R;
    for (int i = 0; i < N; ++i) {
        std::vector<pair<int,int>> v2;
        g->graph.push_back(v2);
    }
    for (int i = 0; i < M; ++i) {
        if(W)
            g->graph[get<0>(graph[i])-1].push_back(make_pair(get<1>(graph[i]), get<2>(graph[i])));
        else
            g->graph[get<0>(graph[i])-1].push_back(make_pair(get<1>(graph[i]), 1));
    }
    return g;
}

GraphBase *GraphListOfEdges::transformToAdjMatrix()
{
    GraphAdjMatrix *g = new GraphAdjMatrix();
    g->N = N;
    g->W = W;
    for (int i = 0; i < N; ++i) {
        std::vector<int> tv;
        for (int i = 0; i < N; ++i) {
            tv.push_back(0);
        }
        g->graph.push_back(tv);
    }
    for(int i =0;i < M ;i++) {
        g->graph[get<0>(graph[i])-1][get<1>(graph[i])-1] = get<2>(graph[i]);
        if(R == 0)
            g->graph[get<1>(graph[i])-1][get<0>(graph[i])-1] = get<2>(graph[i]);
    }
    return g;
}
