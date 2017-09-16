#include "graphlistofedges.h"
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>

using namespace std;

GraphListOfEdges::GraphListOfEdges() : GraphBase('E') {}

GraphListOfEdges::GraphListOfEdges(const std::pair<SpainingTree, int> &set) : GraphBase('E')
{
    NTops = set.second;
    auto edges = set.first;
    auto Size = edges.size();
    is_directed = false;
    is_weighted = true;
    data = Edges();
    for(std::size_t i = 0; i<Size; i++)
    {
        int from,to,w;
        std::tie(from,to,w) = edges[i];
        data.insert(std::make_pair(from,std::make_pair(to,w)));
    }
}

GraphListOfEdges::~GraphListOfEdges() {}

void GraphListOfEdges::Fill(ifstream &in)
{
    std::size_t Size;
    in>>NTops;
    in>>Size;
    in>>is_directed;
    in>>is_weighted;
    data = Edges();
    for(std::size_t i = 0; i<Size; i++)
    {
        int from;
        int to;
        in>>from;
        in>>to;
        from--;
        to--;
        if(is_weighted)
        {
            int w;
            in>>w;
            data.insert(std::make_pair(from,std::make_pair(to,w)));
        }
        else
            data.insert(std::make_pair(from,std::make_pair(to,1)));
    }
}

void GraphListOfEdges::Write(ostream &out)
{
    out<<NTops<<' '<<data.size()<<'\n';
    out<<is_directed<<' '<<is_weighted<<'\n';
    for(const auto &el : data)
    {
        auto value = el.second;
        if(is_weighted)
            out<<el.first+1<<' '<<value.first+1<<' '<<value.second;
        else
            out<<el.first+1<<' '<<value.first+1;
        out<<'\n';
    }
}

void GraphListOfEdges::addEdge(int from, int to, int weight)
{
    data.insert(std::make_pair(from,std::make_pair(to,weight)));
    if(!is_directed)
        data.insert(
                    std::make_pair(to,std::make_pair(from,weight)));
}

void GraphListOfEdges::removeEdge(int from, int to)
{
    erase(from,to);
    if(!is_directed)
        erase(to,from);
}

int GraphListOfEdges::changeEdge(int from, int to, int newWeight)
{
    int oldWeight;
    auto range = data.equal_range(from);
    for (auto it = range.first; it != range.second;)
    {
        if (it->second.first == to)
        {
            oldWeight = it->second.second;
            it->second.second = newWeight;
            break;
        }
        else
            ++it;
    }
    if(is_directed)
        return oldWeight;
    range = data.equal_range(to);
    for (auto it = range.first; it != range.second;)
    {
        if (it->second.first == from)
        {
            it->second.second = newWeight;
            return oldWeight;
        }
        else
            ++it;
    }
    return oldWeight;
}

std::pair<SpainingTree, int> GraphListOfEdges::getSpainingTreePrima()
{
    int V = NTops;
    std::vector<int> key(V,std::numeric_limits<int>::max());
    std::vector<int> mstSet(V,-1);

    SpainingTree R(V-1);
    std::set<std::pair<int,int>> q;
    q.insert (std::make_pair (0, 0));
    std::vector<bool> used(V,false);
    auto copy = data;
    for(const auto &el : data)
    {
        auto from = el.first;
        auto to = el.second.first;
        auto w = el.second.second;
        copy.insert(
                    std::make_pair(to,std::make_pair(from,w)));
    }

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

        auto range = copy.equal_range(v);
        for (auto it = range.first; it != range.second; ++it)
        {
            auto j = it->second.first;
            auto w = it->second.second;
            if (!used[j] && w <  key[j])
            {
                q.erase (std::make_pair(key[j], j));
                key[j] = w;
                mstSet[j] = v;
                q.insert (std::make_pair (key[j], j));
            }
        }
    }

    for (int i = 1; i < V; i++)
        R[i-1] = std::make_tuple(i, mstSet[i], key[i]);

    return std::make_pair(R,V);
}

std::pair<SpainingTree, int> GraphListOfEdges::getSpainingTreeKruscal()
{
    int V = data.size();
    SpainingTree result;

    SpainingTree SortedEdges(V);
    std::size_t j = 0;
    for(const auto &el : data)
        SortedEdges[j++] =
                std::make_tuple(el.first,el.second.first,el.second.second);

    std::sort(SortedEdges.begin(),SortedEdges.end(),
              [](EdgeTuple &a,EdgeTuple &b)
    {
        return std::get<2>(a)<std::get<2>(b);
    });

    DSU subsets = DSU(V);


    for(const auto &el : SortedEdges)
    {
        int x = subsets.find(std::get<0>(el));
        int y = subsets.find(std::get<1>(el));

        if (x != y)
        {
            result.push_back(el);
            subsets.unite(x, y);
        }
    }
    return std::make_pair(result,NTops);
}

std::pair<SpainingTree, int> GraphListOfEdges::getSpainingTreeBoruvka()
{
    int E = data.size();
    SpainingTree edges(E);
    std::size_t j = 0;
    SpainingTree result(NTops-1);
    for(const auto &el : data)
        edges[j++] =
                std::make_tuple(el.first,el.second.first,el.second.second);

    std::sort(edges.begin(),edges.end(),
              [](EdgeTuple &a,EdgeTuple &b)
    {
        return std::get<2>(a)<std::get<2>(b);
    });

    DSU subsets = DSU(NTops);

    int numTrees = NTops;
    auto index = 0;

    for (std::size_t t = 1; t < NTops && numTrees > 1; t = t + t)
    {
        std::vector<int> cheapest(NTops,-1);
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
        for (std::size_t i=0; i<NTops; i++)
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
    return std::make_pair(result,NTops);
}

int GraphListOfEdges::CheckEuler(bool &circleExist)
{
    //проверка на 2-ой критерий
    std::vector<int> parent(NTops,-1);
    circleExist = false;
    for(const auto &el : data)
    {
        int x = DSU::find(parent,el.first);
        int y = DSU::find(parent, el.second.first);

        if (x == y)
        {
            circleExist = true;
            break;
        }

        DSU::Union(parent, x, y);
    }
    if(!circleExist)
        return 0;
    auto copy = data;
    for(const auto &el : data)
    {
        auto from = el.first;
        auto to = el.second.first;
        auto w = el.second.second;
        copy.insert(
                    std::make_pair(to,std::make_pair(from,w)));
    }
    int count = 0,top = 1;
    for(int i =0; i<int(NTops); i++)
    {
        if(copy.count(i)%2!=0)
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

std::vector<int> GraphListOfEdges::getEuleranTourFleri()
{
    bool is_circle;
    auto v = CheckEuler(is_circle);
    if(!v)
        return std::vector<int> {};
    v--;
    std::vector<int> R(data.size()+1);
    auto copy = data;
    for(const auto &el : data)
    {
        auto from = el.first;
        auto to = el.second.first;
        auto w = el.second.second;
        copy.insert(
                    std::make_pair(to,std::make_pair(from,w)));
    }
    R[0] = v+1;
    proc(v,copy,R);
    return R;
}

std::vector<int> GraphListOfEdges::getEuleranTourEffective()
{
    bool is_circle;
    auto v = CheckEuler(is_circle);
    if(!v)
        return std::vector<int> {};
    v--;
    std::vector<int> R(data.size()+1,0);
    auto copy = data;
    for(const auto &el : data)
    {
        auto from = el.first;
        auto to = el.second.first;
        auto w = el.second.second;
        copy.insert(
                    std::make_pair(to,std::make_pair(from,w)));
    }
    std::stack<int> S;
    S.push(v);
    std::size_t count = 0;
    while (!S.empty())
    {
        auto w = S.top();
        auto it = copy.find(w);
        if(it != copy.cend())
        {
            auto u = it->second.first;
            S.push(u);
            erase(copy,w,u);
            if(!is_directed)
                erase(copy,u,w);
        }

        if(w==S.top())
        {
            S.pop();
            R[count++]=w+1;
        }
    }
    return R;
}

void GraphListOfEdges::erase(int from, int to)
{
    erase(data,from,to);
}

void GraphListOfEdges::erase(Edges &d, int from, int to)
{
    auto range = d.equal_range(from);
    for (auto it = range.first; it != range.second;)
    {
        if (it->second.first == to)
            it = d.erase(it);
        else
            ++it;
    }
}

int GraphListOfEdges::DFSCount(int v, std::vector<bool> &visited, const Edges &copy)
{
    visited[v] = true;
    int count = 1;

    auto range = copy.equal_range(v);
    for (auto it = range.first; it != range.second; it++)
    {
        auto j = it->first;
        if (!visited[j])
            count += DFSCount(j, visited,copy);
    }
    return count;
}

bool GraphListOfEdges::isValidNextEdge(int u, int v, Edges &copy)
{
    int count1 = 0;
    auto range = copy.equal_range(u);
    for (auto it = range.first; it != range.second; it++)
        if (it->second.second)
            count1++;

    if(count1==1)
        return true;

    std::vector<bool> visited(copy.size(),false);
    count1 = DFSCount(u, visited,copy);

    auto r = copy.equal_range(v);
    for (auto it = range.first; it != range.second; it++)
        if (it->second.first == v)
            it->second.second = 0;
    if(!is_directed)
    {
        for (auto it = r.first; it != r.second; it++)
            if (it->second.first == u)
                it->second.second = 0;
    }

    std::fill(visited.begin(),visited.end(),false);
    int count2 = DFSCount(u, visited,copy);
    for (auto it = range.first; it != range.second; it++)
        if (it->second.first == v)
            it->second.second = 1;
    if(!is_directed)
    {
        for (auto it = r.first; it != r.second; it++)
            if (it->second.first == u)
                it->second.second = 1;
    }

    return (count1 > count2)? false: true;
}

void GraphListOfEdges::proc(int u, Edges &copy, std::vector<int> &R)
{
    static int index = 0;
    auto range = copy.equal_range(u);
    for (auto it = range.first; it != range.second; it++)
    {
        auto v = it->second.first;
        if(it->second.second && isValidNextEdge(u, v,copy) )
        {
            R[++index]=v+1;
            it->second.second = 0;
            if(!is_directed)
            {
                auto r = copy.equal_range(v);
                for (auto z = r.first; z != r.second; z++)
                    if (z->second.first == u)
                        z->second.second = 0;

            }
            proc(v,copy,R);
        }
    }

}
