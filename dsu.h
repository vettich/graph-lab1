#ifndef DSU_H
#define DSU_H

#include <vector>

struct disjoint_set
{
    int parent;
    unsigned rank;
    disjoint_set(int i) : parent(i), rank(0) { }
};
class DSU
{
    std::vector<disjoint_set> forest;

public:
    DSU(int n);
    int find(int i);
    void unite(int x, int y);

    static int find(const std::vector<int> &parent, int i);
    static void Union(std::vector<int> &parent, int x, int y);
};

#endif // DSU_H
