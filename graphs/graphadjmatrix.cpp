#include "graphadjmatrix.h"
#include "graphadjlist.h"
#include "graphlistofedges.h"
#include <fstream>
#include <iostream>

using namespace std;


GraphAdjMatrix::GraphAdjMatrix() : GraphBase('C') {}

void GraphAdjMatrix::Fill(ifstream &in)
{
    std::size_t Size;
    in >> Size;
    in >> is_directed;
    in >> is_weighted;

    data = Matrix(Size,IntVec(Size,0));
    for(std::size_t i=0; i<Size; i++)
        for(std::size_t j = 0; j<Size; j++)
    in>>data[i][j];
}

void GraphAdjMatrix::Write(ostream &out)
{
    std::size_t Size = data.size();
    out << Size << endl;
    out << is_directed << ' ';
    out << is_weighted << endl;
    for(std::size_t i=0; i<Size; i++)
    {
        for(std::size_t j = 0; j<Size; j++)
            out<<data[i][j]<<' ';
        out<<'\n';
    }
}

void GraphAdjMatrix::addEdge(int from, int to, int weight)
{
    data[from][to] = weight;
    data[to][from] = weight;
}

void GraphAdjMatrix::removeEdge(int from, int to)
{
    data[from][to] = 0;
    data[to][from] = 0;
}

int GraphAdjMatrix::changeEdge(int from, int to, int newWeight)
{
    auto oldWeight = data[from][to];
    data[from][to] = newWeight;
    data[to][from] = newWeight;
    return oldWeight;
}

std::pair<SpainingTree, int> GraphAdjMatrix::getSpainingTreePrima()
{
    int V = data.size();
    std::vector<int> key(V,std::numeric_limits<int>::max());
    std::vector<int> mstSet(V,-1);

    SpainingTree R(V-1);
    std::set<std::pair<int,int>> q;
    q.insert (std::make_pair (0, 0));
    std::vector<bool> used(V,false);
    for (int i=0; i<V; ++i)
    {
        if (q.empty())
        {
            std::cout << "No MST!";
            exit(0);
        }
        int v = q.begin()->second;

        q.erase (q.begin());

        if (mstSet[v] != -1)
            used[v] = true;

        for (int j=0; j<V; ++j)
        {
            int cost = data[v][j];
            if (cost && !used[j] &&  cost < key[j])
            {
                q.erase (std::make_pair(key[j], j));
                key[j] = cost;
                mstSet[j] = v;
                q.insert (std::make_pair (key[j], j));
            }
        }
    }

    for (int i = 1; i < V; i++)
        R[i-1] = std::make_tuple(i, mstSet[i], key[i]);
    return std::make_pair(R,V);
}

std::pair<SpainingTree, int> GraphAdjMatrix::getSpainingTreeKruscal()
{
    SpainingTree SortedEdges;
    int V = data.size();
    for(int i = 0; i<V; i++)
    {
        for(int j = 0; j<V; j++)
        {
            auto el = data[i][j];
            if(el)
                SortedEdges.push_back(std::make_tuple(i,j,el));
        }
    }

    SpainingTree result(V-1);
    std::sort(SortedEdges.begin(),SortedEdges.end(),
              [](EdgeTuple &a,EdgeTuple &b)
    {
        return std::get<2>(a)<std::get<2>(b);
    });
    DSU subsets = DSU(V);

    std::size_t j = 0;
    for(const auto &el : SortedEdges)
    {
        int x = subsets.find(std::get<0>(el));
        int y = subsets.find(std::get<1>(el));

        if (x != y)
        {
            result[j++]=el;
            subsets.unite(x, y);
        }
    }

    return std::make_pair(result,V);
}

std::pair<SpainingTree, int> GraphAdjMatrix::getSpainingTreeBoruvka()
{
    SpainingTree edges;
    int V = data.size();
    for(int i = 0; i<V; i++)
    {
        for(int j = 0; j<V; j++)
        {
            auto el = data[i][j];
            if(el)
                edges.push_back(std::make_tuple(i,j,el));
        }
    }

    SpainingTree result(V-1);
    std::sort(edges.begin(),edges.end(),
              [](EdgeTuple &a,EdgeTuple &b)
    {
        return std::get<2>(a)<std::get<2>(b);
    });
    DSU subsets = DSU(V);

    int numTrees = V;
    auto index = 0;
    int E = edges.size();
    for (int t = 1; t < V && numTrees > 1; t = t + t)
    {
        std::vector<int> cheapest(V,-1);
        for (int i=0; i<E; i++)
        {
            int set1 = subsets.find(std::get<0>(edges[i]));
            int set2 = subsets.find(std::get<1>(edges[i]));
            if (set1 == set2)
                continue;

            else
            {
                if (cheapest[set1] == -1 ||
                        std::get<2>(edges[cheapest[set1]]) > std::get<2>(edges[i]))
                    cheapest[set1] = i;

                if (cheapest[set2] == -1 ||
                        std::get<2>(edges[cheapest[set2]]) > std::get<2>(edges[i]))
                    cheapest[set2] = i;
            }
        }
        for (int i=0; i<V; i++)
        {
            // Check if cheapest for current set exists
            if (cheapest[i] != -1)
            {
                int set1 = subsets.find(std::get<0>(edges[cheapest[i]]));
                int set2 = subsets.find(std::get<1>(edges[cheapest[i]]));
                if (set1 == set2)
                    continue;
                //MSTweight += std::get<2>(edge[cheapest[i]]);
                result[index++] = edges[cheapest[i]];
                subsets.unite(set1,set2);
                numTrees--;
            }
        }

    }
    return std::make_pair(result,V);
}

int GraphAdjMatrix::CheckEuler(bool &circleExist)
{
    int NTops = data.size();
    std::vector<int> parent(NTops,-1);
    circleExist = false;
    for(int i=0; i<NTops; i++)
        for(int j=0; j<NTops; j++)
        {
            if(!data[i][j])
                continue;
            int x = DSU::find(parent, i);
            int y = DSU::find(parent, j);

            if (x == y)
            {
                circleExist = true;
                break;
            }

            DSU::Union(parent, x, y);
        }
    if(!circleExist)
        return 0;

    int count = 0,top = 1;

    for(int i=0; i<NTops; i++)
    {
        auto temp = NTops-std::count(data[i].cbegin(),data[i].cend(),0);
        if(temp%2!=0)
        {
            top = i+1;
            count++;
        }
    }
    if(count>2)
        return 0;
    else if(count == 0)
        circleExist = true;
    else
        circleExist = false;
    return top;
}

std::vector<int> GraphAdjMatrix::getEuleranTourFleri()
{
    bool is_circle;
    auto v = CheckEuler(is_circle);
    if(!v)
        return std::vector<int> {};
    v--;
    std::vector<int> R;
    R.reserve(2*data.size());
    auto copy = data;
    R.push_back(v+1);
    proc(v,copy,R);
    return R;
}

std::vector<int> GraphAdjMatrix::getEuleranTourEffective()
{
    bool is_circle;
    auto v = CheckEuler(is_circle);
    if(!v)
        return std::vector<int> {};
    v--;
    std::vector<int> R;
    R.reserve(2*data.size());
    auto copy = data;
    std::stack<int> S;
    S.push(v);
    int Size = data.size();
    while (!S.empty())
    {
        auto w = S.top();
        for(int u=0; u<Size; u++)
            if(copy[w][u])
            {
                S.push(u);
                copy[w][u]=0;
                if(!is_directed)
                    copy[u][w]=0;
                break;
            }

        if(w==S.top())
        {
            S.pop();
            R.push_back(w+1);
        }
    }
    return R;
}

int GraphAdjMatrix::DFSCount(int v, std::vector<bool> &visited, const Matrix &copy)
{
    visited[v] = true;
    int count = 1;

    for(auto j=0; j<int(copy.size()); j++)
        if (!visited[j])
                count += DFSCount(j, visited,copy);
    return count;
}

bool GraphAdjMatrix::isValidNextEdge(int u, int v, Matrix &copy)
{
    if((copy.size()-std::count(data[u].cbegin(),data[u].cend(),0))==1)
        return true;

    std::vector<bool> visited(copy.size(),false);
    int count1 = DFSCount(u, visited,copy);

    copy[u][v] = 0;
    if(!is_directed)
        copy[v][u] = 0;

    std::fill(visited.begin(),visited.end(),false);
    int count2 = DFSCount(u, visited,copy);
    copy[u][v] = 1;
    if(!is_directed)
        copy[v][u] = 1;

    return (count1 > count2)? false: true;
}

void GraphAdjMatrix::proc(int u, Matrix &copy, std::vector<int> &R)
{
    for(auto v=0; v<int(copy.size()); v++)
    {
        if(copy[u][v] && isValidNextEdge(u, v,copy) )
        {
            R.push_back(v+1);
            copy[u][v] = 0;
            if(!is_directed)
                copy[v][u] = 0;
            proc(v,copy,R);
        }
    }
}

