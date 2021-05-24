#ifndef INDUCED_GRAPH
#define INDUCED_GRAPH

#include "types.cpp"
#include "constants.cpp"

Graph* inducedGraph(CostMatrix*, vector<Vertex>*);

Graph* inducedGraph(CostMatrix *graph, vector<Vertex> *vertices)
{
    size_t dimIndGraph = vertices->size();
    auto indGraph = new Graph(dimIndGraph);
    for(Vertex u=0; (size_t)u<dimIndGraph; ++u) {
        for(auto & v : *vertices) {
            v = 0;
        }
    }

    return indGraph;
}

#endif