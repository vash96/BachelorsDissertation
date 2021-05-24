#ifndef PRINT
#define PRINT

#include "types.cpp"

void print(ostream & out, SpanningTree *tree)
{
    for(auto & edge : *tree) {
        out << "{" << edge.first << ", " << edge.second << "} ";
    }
    out << endl;
}

void print(ostream & out, Tour *tour)
{
    for(auto & v : *tour) {
        out << v << " ";
    }
    out << endl;
}

#endif