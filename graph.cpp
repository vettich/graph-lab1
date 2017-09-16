#include "graph.h"

#include <iostream>
#include <fstream>
#include <map>
#include "graphs/graphadjlist.h"
#include "graphs/graphadjmatrix.h"
#include "graphs/graphlistofedges.h"

using namespace std;


struct TransformView
{
    static GraphAdjMatrix* MatrixFromLists(const GraphAdjList *lists)
    {
        auto R = new GraphAdjMatrix();
        auto Size = lists->data.size();
        R->data = Matrix(Size,IntVec(Size,0));
        R->is_weighted = lists->is_weighted;
        R->is_directed = lists->is_directed;
        for(std::size_t i = 0; i<Size; i++)
        {
            for(const auto &el : lists->data[i])
                if(lists->is_weighted)
                    R->data[i][el.first]=el.second;
                else
                    R->data[i][el.first]=1;
        }
        return R;
    }
    static GraphAdjMatrix* MatrixFromEList(const GraphListOfEdges *lists)
    {
        auto R = new GraphAdjMatrix();
        auto Size = lists->NTops;

        R->data = Matrix(Size,IntVec(Size,0));
        R->is_weighted = lists->is_weighted;
        R->is_directed = lists->is_directed;

        for(const auto &el : lists->data)
        {
            if(lists->is_weighted)
                R->data[el.first][el.second.first]=el.second.second;
            else
                R->data[el.first][el.second.first]=1;
            if(!lists->is_directed)
            {
                if(lists->is_weighted)
                    R->data[el.second.first][el.first]=el.second.second;
                else
                    R->data[el.second.first][el.first]=1;
            }
        }
        return R;
    }
    static GraphAdjList* AListFromMatrix(const GraphAdjMatrix *matrix)
    {
        auto R = new GraphAdjList();
        auto Size = matrix->data.size();
        R->data = Lists(Size,List());
        R->is_weighted = matrix->is_weighted;
        R->is_directed = matrix->is_directed;

        for(std::size_t i = 0; i<Size; i++)
        {
            for(std::size_t j = 0; j<Size; j++)
            {
                auto el = matrix->data[i][j];
                if(el)
                    R->data[i][j]=el;
            }
        }
        return R;
    }
    static GraphAdjList* AListFromEList(const GraphListOfEdges *lists)
    {
        auto R = new GraphAdjList();
        auto Size = lists->NTops;
        R->data = Lists(Size,List());
        R->is_weighted = lists->is_weighted;
        R->is_directed = lists->is_directed;

        for(const auto &el : lists->data)
        {
            if(lists->is_weighted)
                R->data[el.first][el.second.first]=el.second.second;
            else
                R->data[el.first][el.second.first]=1;

            if(!lists->is_directed)
            {
                if(lists->is_weighted)
                    R->data[el.second.first][el.first]=el.second.second;
                else
                    R->data[el.second.first][el.first]=1;
            }
        }
        return R;
    }
    static GraphListOfEdges* EListFromMatrix(const GraphAdjMatrix *matrix)
    {
        auto R = new GraphListOfEdges();
        auto Size = matrix->data.size();
        R->data = Edges();
        R->is_weighted = matrix->is_weighted;
        R->is_directed = matrix->is_directed;
        R->NTops = Size;

        for(std::size_t i = 0; i<Size; i++)
        {
            for(std::size_t j = i+1; j<Size; j++)
            {
                auto el = matrix->data[i][j];
                if(el)
                    R->data.insert(std::make_pair(i, std::make_pair(j,el)));
            }
        }
        if(!R->is_directed)
            return R;
        for(std::size_t i = 0; i<Size; i++)
        {
            for(std::size_t j = i+1; j<Size; j++)
            {
                auto el = matrix->data[j][i];
                if(el)
                    R->data.insert(std::make_pair(j, std::make_pair(i,el)));
            }
        }
        return R;
    }
    static GraphListOfEdges* EListFromLists(const GraphAdjList *lists)
    {
        auto R = new GraphListOfEdges();
        auto Size = lists->data.size();
        R->data = Edges();
        R->is_weighted = lists->is_weighted;
        R->is_directed = lists->is_directed;
        R->NTops = Size;

        for(std::size_t i = 0; i<Size; i++)
        {
            for(const auto &el : lists->data[i])
                if(lists->is_weighted)
                    R->data.insert(std::make_pair(i,std::make_pair(el.first,el.second)));
                else
                    R->data.insert(std::make_pair(i,std::make_pair(el.first,1)));
        }
        return R;
    }
};


Graph::Graph() : data(nullptr) {}

Graph::~Graph()
{
    delete data;
}

void Graph::readGraph(string fileName)
{
    std::ifstream in(fileName);
    if(!in)
        return;
    char type;
    in >> type;
    if(type=='C')
    {
        data = new GraphAdjMatrix();
        data->Fill(in);
    }
    else if(type=='L')
    {
        data = new GraphAdjList();
        data->Fill(in);
    }
    else if(type=='E')
    {
        data = new GraphListOfEdges();
        data->Fill(in);
    }
}

void Graph::addEdge(int from, int to, int weight)
{
    data->addEdge(from,to,weight);
}

void Graph::removeEdge(int from, int to)
{
    data->removeEdge(from,to);
}

int Graph::changeEdge(int from, int to, int newWeight)
{
    return data->changeEdge(from,to,newWeight);
}

void Graph::transformToAdjList()
{
    if(data->type=='C')
    {
        GraphBase* update = TransformView::AListFromMatrix(dynamic_cast<GraphAdjMatrix*>(data));
        delete data;
        data = update;
    }
    else if(data->type=='L')
    {
        return;
    }
    else if(data->type=='E')
    {
        GraphBase* update = TransformView::AListFromEList((GraphListOfEdges*)(data));
        delete data;
        data = update;
    }
}

void Graph::transformToAdjMatrix()
{
    if(data->type=='C')
    {
        return;
    }
    else if(data->type=='L')
    {
        GraphBase* update = TransformView::MatrixFromLists(dynamic_cast<GraphAdjList*>(data));
        delete data;
        data = update;
    }
    else if(data->type=='E')
    {
        GraphBase* update = TransformView::MatrixFromEList((GraphListOfEdges*)(data));
        delete data;
        data = update;
    }
}

void Graph::transformToListOfEdges()
{
    if(data->type=='C')
    {
        GraphBase* update = TransformView::EListFromMatrix(dynamic_cast<GraphAdjMatrix*>(data));
        delete data;
        data = update;
    }
    else if(data->type=='L')
    {
        GraphBase* update = TransformView::EListFromLists(dynamic_cast<GraphAdjList*>(data));
        delete data;
        data = update;
    }
    else if(data->type=='E')
    {
        return;
    }
}

void Graph::writeGraph(string fileName)
{
    std::ofstream out(fileName);
    if(!out)
        return;

    out << data->type << ' ';
    data->Write(out);
}

Graph Graph::getSpainingTreePrima() const
{
    std::pair<SpainingTree,int> R;
    //матрица
    if(data->type=='C')
    {
        R = data->getSpainingTreePrima();
    }
    //списки смежности
    else if(data->type=='L')
    {
        R = data->getSpainingTreePrima();
    }
    //списки ребер
    else if(data->type=='E')
    {
        R = data->getSpainingTreePrima();
    }
    Graph g;
    g.data = new GraphListOfEdges(R);
    return g;
}

Graph Graph::getSpainingTreeKruscal() const
{
    std::pair<SpainingTree,int> R;
    //матрица
    if(data->type=='C')
    {
        R = data->getSpainingTreeKruscal();
    }
    //списки смежности
    else if(data->type=='L')
    {
        R = data->getSpainingTreeKruscal();
    }
    //списки ребер
    else if(data->type=='E')
    {
        R = data->getSpainingTreeKruscal();
    }
    Graph g;
    g.data = new GraphListOfEdges(R);
    return g;
}

Graph Graph::getSpainingTreeBoruvka() const
{
    std::pair<SpainingTree,int> R;
    //матрица
    if(data->type=='C')
    {
        R = data->getSpainingTreeBoruvka();
    }
    //списки смежности
    else if(data->type=='L')
    {
        R = data->getSpainingTreeBoruvka();
    }
    //списки ребер
    else if(data->type=='E')
    {
        R = data->getSpainingTreeBoruvka();
    }
    Graph g;
    g.data = new GraphListOfEdges(R);
    return g;
}

int Graph::CheckEuler(bool &circleExist)
{
    return data->CheckEuler(circleExist);
}

std::vector<int> Graph::getEuleranTourFleri()
{
    return data->getEuleranTourFleri();
}

std::vector<int> Graph::getEuleranTourEffective()
{
    return data->getEuleranTourEffective();
}

char Graph::type()
{
    return !!data ? data->type:'~';
}

bool Graph::isGraph()
{
    return !!data;
}

void Graph::print()
{
    if(!data) {
        cout << "~" << endl;
    }
    cout << data->type << ' ';
    data->print();
}
