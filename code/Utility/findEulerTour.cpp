#ifndef EULER_TOUR
#define EULER_TOUR

#include "constants.cpp"
#include "types.cpp"
#include "fromListToTour.cpp"
#include "shortcutTour.cpp"

#include <algorithm> // Random shuffle
#include <stack>
using namespace std;

Tour* findEulerTour(size_t, SpanningTree*, Matching*);
void eulerDFS(TourList*, TourList::iterator, Vertex, GraphLabeled&, BoolVec&);

Tour* findEulerTour(size_t dimGraph, SpanningTree *mst, Matching *matching)
{
    size_t nOfEdges = mst->size() + matching->size();
    size_t cnt = 0;

    // First, construct the multigraph: labels on edges are used to determine the index on "visited" array
    GraphLabeled multigraph(dimGraph);

    for(auto & edge : *mst) { // Edges from original mst
        Vertex u = edge.first;
        Vertex v = edge.second;

        multigraph[u].push_back({v, cnt});
        multigraph[v].push_back({u, cnt+nOfEdges});

        ++cnt;
    }
    for(auto & edge : *matching) {
        Vertex u = edge.first;
        Vertex v = edge.second;

        multigraph[u].push_back({v, cnt});
        multigraph[v].push_back({u, cnt+nOfEdges});

        ++cnt;
    }

    // Time to construct the circuit (in TourList form)
    auto eulerList = new TourList;
    BoolVec visited(2*nOfEdges, false);
    eulerDFS(eulerList, eulerList->begin(), 0, multigraph, visited);

    // Shortcut tour
    shortcutTour(dimGraph, eulerList);

    // Convert the tourList to get a proper Tour
    auto tour = fromListToTour(eulerList);

    delete eulerList;

    return tour;
}


void eulerDFS(TourList *tourList, TourList::iterator it, Vertex u, GraphLabeled & graph, BoolVec & visited)
{
    size_t nOfEdges = visited.size() / 2;

    // Insert u at position it
    it = tourList->insert(it, u);

    // For each incident edge
    for(auto & edge : graph[u]) {
        if(not visited[edge.second]) {
            // Visiting an edge and its "reverse"
            visited[edge.second] = visited[(edge.second+nOfEdges) % (2*nOfEdges)] = true;
            eulerDFS(tourList, it, edge.first, graph, visited);
        }
    }
}

#endif