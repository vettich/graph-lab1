#ifndef GRAPHBASE_H
#define GRAPHBASE_H

#include <string>

class GraphBase
{
public:
    GraphBase();
    GraphBase(std::string filename);
    GraphBase(std::ifstream& file);
    virtual ~GraphBase();
    virtual void init();
    void read(std::string filename);
    virtual void read(std::ifstream& file);
    void write(std::string filename);
    virtual void write(std::ofstream& file);
    virtual void addEdge(int from, int to, int weight);
    virtual void removeEdge(int from, int to);
    virtual int changeEdge(int from, int to, int newWeight);
};

#endif // GRAPHBASE_H
