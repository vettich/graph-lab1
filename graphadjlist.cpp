#include "graphadjlist.h"
#include "graphadjmatrix.h"
#include "graphlistofedges.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

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
    vector <int> temp;
    int n;
    while (!file.eof()) {
        stringstream ss;
        string s;
        getline(file, s);
        ss << s;
        while(ss >> n) {
            temp.push_back(n);
        }
        if (!temp.empty()) {
            vector <pair <int,int>> temp2;
            if(!W) {
                for(size_t j = 0; j < temp.size(); j++) {
                    temp2.push_back(make_pair(temp[j], 1));
                }
            } else {
                for(size_t j = 0; j < temp.size(); j += 2) {
                    temp2.push_back(make_pair(temp[j],temp[j+1]));
                }
            }
            graph.push_back(temp2);
            temp.clear();
        }
    }
}

void GraphAdjList::write(std::ofstream &file)
{
    file << N << endl;
    file << R << endl;
    file << W << endl;
    for(size_t i = 0; i < graph.size(); i++)
    {
        for(size_t j = 0; j < graph[i].size(); j++)
            if(!W)
                file << graph[i][j].first << ' ';
            else
                file << graph[i][j].first << ' ' << graph[i][j].second << ' ';
        file << endl;
    }
}

void GraphAdjList::addEdge(int from, int to, int weight)
{
    graph[from-1].push_back(make_pair(to, weight));
    graph[to-1].push_back(make_pair(from, weight));
    N++;
}

void GraphAdjList::removeEdge(int from, int to)
{
    for(size_t j = 0; j < graph[from - 1].size(); j++) {
        if(graph[from-1][j].first == to) {
            graph[from-1].erase(graph[from-1].begin() + j);
        }
        if(graph[to-1][j].first == from) {
            graph[to-1].erase(graph[to-1].begin() + j);
        }
    }
    N--;
}

int GraphAdjList::changeEdge(int from, int to, int newWeight)
{
    int oldWeight = 0;
    for(size_t j = 0; j < graph[from - 1].size(); j++) {
        if(graph[from-1][j].first == to) {
            oldWeight = graph[from-1][j].second;
            graph[from-1][j].second = newWeight;
        }
        if(graph[to-1][j].first == from) {
            oldWeight = graph[to-1][j].second;
            graph[to-1][j].second = newWeight;
        }
    }
    return oldWeight;
}

GraphBase *GraphAdjList::transformToAdjMatrix()
{
    GraphAdjMatrix * g = new GraphAdjMatrix();
    g->N = N;
    g->W = W;
    for (int i = 0; i < N; ++i) {
        std::vector<int> tv;
        for (int i = 0; i < N; ++i) {
            tv.push_back(0);
        }
        g->graph.push_back(tv);
    }
    for (size_t i = 0; i <graph.size(); ++i)
        while(!graph[i].empty())
        {
            if(W)
                g->graph[i][graph[i].back().first-1] = graph[i].back().second;
            else
                g->graph[i][graph[i].back().first-1] = 1;
            if(R) {
                if(W)
                    g->graph[graph[i].back().first-1][i] = graph[i].back().second;
                else
                    g->graph[graph[i].back().first-1][i] = 1;
            }
            graph[i].pop_back();
        }
    return g;
}

GraphBase *GraphAdjList::transformToListOfEdges()
{
    GraphListOfEdges *g = new GraphListOfEdges();
    g->N = N;
    g->R = R;
    g->W = W;
    g->M = 0;
    for (int i = 0; i < N; ++i) {
        while(!graph[i].empty()) {
            if(W)
                g->graph.push_back(make_tuple(i+1, graph[i].back().first, graph[i].back().second));
            else
                g->graph.push_back(make_tuple(i+1, graph[i].back().first, 1));
            g->M++;
            if(R == 1) {
                if(W)
                    g->graph.push_back(make_tuple(graph[i].back().first, i+1, graph[i].back().second));
                else
                    g->graph.push_back(make_tuple(graph[i].back().first, i+1, 1));
                g->M++;
            }
            graph[i].pop_back();
        }
    }
    return g;
}
