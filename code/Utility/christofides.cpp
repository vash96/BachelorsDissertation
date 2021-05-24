#ifndef CHRISTOFIDES
#define CHRISTOFIDES

#include "types.cpp"
#include "constants.cpp"

Tour* christofides(CostMatrix *graph, Vertex initialVertex)
{
    auto mstOut = primMst(graph, initialVertex);
    auto mstGraph = mstOut.first;

    // Convert mst from "Graph form" to "SpanningTree" form
    auto mst = new SpanningTree();
    mst->reserve(graph->size());
    for(Vertex u=0; (size_t)u<graph->size(); ++u) {
        for(auto & v : (*mstGraph)[u]) {
            if(u < v) {
                mst->emplace_back(u, v);
            }
        }
    }

    auto oddVert = oddDegreeVertices(mstGraph);
    auto matching = greedyMinimumWeightMatching(graph, oddVert);

    auto eulerTour = findEulerTour(graph->size(), mst, matching);

    delete mstGraph;
    delete mst;
    delete oddVert;
    delete matching;

    return eulerTour;
}

#endif