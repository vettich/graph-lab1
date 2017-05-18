#ifndef GRAPHBASE_H
#define GRAPHBASE_H

#include <string>

class GraphBase
{
public:
    GraphBase();
    GraphBase(std::string filename);
    GraphBase(std::ifstream& file);
    void read(std::string filename);
    void write(std::string filename);
    static GraphBase *create(std::string filename);

    virtual ~GraphBase();
    virtual char type() {return '~';}
    virtual void init();
    virtual void read(std::ifstream& file);
    virtual void write(std::ofstream& file);
    virtual void addEdge(int from, int to, int weight);
    virtual void removeEdge(int from, int to);
    virtual int changeEdge(int from, int to, int newWeight);

    virtual GraphBase *transformToAdjList();
    virtual GraphBase *transformToAdjMatrix();
    virtual GraphBase *transformToListOfEdges();
};

#endif // GRAPHBASE_H
