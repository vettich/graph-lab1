#include "graphadjlist.h"
#include "graphadjmatrix.h"
#include "graphlistofedges.h"
#include "dsu.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

GraphAdjList::GraphAdjList() : GraphBase('L') {}

std::vector<int> Split(const std::string& subject)
{
    std::istringstream ss{subject};
    using StrIt = std::istream_iterator<int>;
    std::vector<int> container{StrIt{ss}, StrIt{}};
    return container;
}

void GraphAdjList::Fill(ifstream &in)
{
    std::size_t Size;
    in>>Size;
    in>>is_directed;
    in>>is_weighted;

    data = Lists(Size,List());
    int key;
    std::string str;
    std::getline(in,str);
    for(std::size_t i = 0; i<Size; i++)
    {
        std::getline(in,str);
        auto vec = Split(str);
        for(std::size_t j = 0; j<vec.size(); j++)
        {
            key = vec[j]-1;
            if(is_weighted)
            {
                data[i][key] = vec[++j];
            }
            else
                data[i][key] = 1;
        }
    }
}

void GraphAdjList::Write(ostream &out)
{
    std::size_t Size = data.size();
    out<<Size<<'\n';
    out<<is_directed<<' '<<is_weighted<<'\n';
    for(std::size_t i = 0; i<Size; i++)
    {
        for(const auto &el : data[i])
            if(is_weighted)
                out<<el.first+1<<' '<<el.second<<' ';
            else
                out<<el.first+1<<' ';
        out<<'\n';
    }
}

void GraphAdjList::addEdge(int from, int to, int weight)
{
    data[from][to] = weight;
    if(!is_directed)
        data[to][from] = weight;
}

void GraphAdjList::removeEdge(int from, int to)
{
    data[from].erase(to);
    if(!is_directed)
        data[to].erase(from);
}

int GraphAdjList::changeEdge(int from, int to, int newWeight)
{
    auto oldWeight = data[from][to];
    data[from][to] = newWeight;
    if(!is_directed)
        data[to][from] = newWeight;
    return oldWeight;
}

std::pair<SpainingTree, int> GraphAdjList::getSpainingTreePrima()
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

        for (const auto &el : data[v])
        {
            int to = el.first;
            int cost = el.second;
            if (!used[to] &&  cost < key[to])
            {
                q.erase (std::make_pair(key[to], to));
                key[to] = cost;
                mstSet[to] = v;
                q.insert (std::make_pair (key[to], to));
            }
        }
    }

    for (int i = 1; i < V; i++)
        R[i-1] = std::make_tuple(i, mstSet[i], key[i]);

    return std::make_pair(R,V);
}

std::pair<SpainingTree, int> GraphAdjList::getSpainingTreeKruscal()
{
    SpainingTree SortedEdges;
    int V = data.size();
    for(int i = 0; i<V; i++)
    {
        for(const auto &el : data[i])
            SortedEdges.push_back(std::make_tuple(i,el.first,el.second));
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

std::pair<SpainingTree, int> GraphAdjList::getSpainingTreeBoruvka()
{
    SpainingTree edges;
    int V = data.size();
    for(int i = 0; i<V; i++)
    {
        for(const auto &el : data[i])
            edges.push_back(std::make_tuple(i,el.first,el.second));
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

int GraphAdjList::CheckEuler(bool &circleExist)
{
    int NTops = data.size();
    std::vector<int> parent(NTops,-1);
    circleExist = false;
    for(int i=0; i<NTops; i++)
        for(const auto &el : data[i])
        {
            int x = DSU::find(parent, i);
            int y = DSU::find(parent, el.first);

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
        if(data[i].size()%2!=0)
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

std::vector<int> GraphAdjList::getEuleranTourEffective()
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
    while (!S.empty())
    {
        auto w = S.top();
        auto map = copy[w];
        if(!map.empty())
        {
            auto u = map.begin()->first;
            S.push(u);
            copy[w].erase(u);
            if(!is_directed)
                copy[u].erase(w);
        }

        if(w==S.top())
        {
            S.pop();
            R.push_back(w+1);
        }
    }
    return R;
}

std::vector<int> GraphAdjList::getEuleranTourFleri()
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

int GraphAdjList::DFSCount(int v, std::vector<bool> &visited, const Lists &copy)
{
    visited[v] = true;
    int count = 1;

    for (auto it = copy[v].begin(); it != copy[v].end(); ++it)
        if (!visited[it->first])
            count += DFSCount(it->first, visited,copy);
    return count;
}

bool GraphAdjList::isValidNextEdge(int u, int v, Lists &copy)
{
    if(copy[u].size()==1)
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

void GraphAdjList::proc(int u, Lists &copy, std::vector<int> &R)
{
    for(const auto &el : copy[u])
    {
        auto v = el.first;
        auto t = el.second;
        if(t && isValidNextEdge(u, v,copy) )
        {
            R.push_back(v+1);
            copy[u][v] = 0;
            if(!is_directed)
                copy[v][u] = 0;
            proc(v,copy,R);
        }
    }
}
