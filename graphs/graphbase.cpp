#include "graphbase.h"
#include <iostream>
#include <fstream>
#include "graphadjlist.h"
#include "graphadjmatrix.h"
#include "graphlistofedges.h"

using namespace std;

GraphBase::GraphBase(char pt) :type(pt) {}

void GraphBase::print() {
    Write(std::cout);
}
