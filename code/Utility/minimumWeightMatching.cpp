#ifndef MIN_WEIGHT_MATCHING
#define MIN_WEIGHT_MATCHING

#include "types.cpp"
#include "constants.cpp"

#include <algorithm> // sort
using namespace std;

// Greedy: each step choose the lightest edge connecting 2 non covered vertices
Matching* greedyMimumWeightMatching(CostMatrix*, vector<Vertex>*);

Matching* greedyMinimumWeightMatching(CostMatrix *graph, vector<Vertex> *vertices)
{
    size_t dimGraph = vertices->size();
    vector<Edge> edges;
    edges.reserve( (dimGraph * (dimGraph-1)) / 2 );

    // Save edges
    for(auto & u : *vertices) {
        for(auto & v : *vertices) {
            if(u < v) {
                edges.emplace_back(u, v);
            }
        }
    }

    // Sort edges by weight
    sort(edges.begin(), edges.end(), [graph](const Edge & e1, const Edge & e2) {
        return costEdge(e1.first, e1.second) < costEdge(e2.first, e2.second);
    });

    BoolVec visited(graph->size(), false);
    auto it = edges.begin();
    auto matching = new Matching;
    matching->reserve(vertices->size());
    for(size_t i=0; i<dimGraph/2; ++i) {
        // Search for the first free edge
        while(visited[it->first] or visited[it->second]) {
            ++it;
        }

        // Add the edge to the matching and set vertices as visited
        matching->push_back(*it);
        visited[it->first] = visited[it->second] = true;
    }

    return matching;
}

#endif