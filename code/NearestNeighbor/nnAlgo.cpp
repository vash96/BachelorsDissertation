#include <bits/stdc++.h>
#include "../Utility/thesis.hpp"
using namespace std;

void doNearestNeighbor(CostMatrix*);
Cost nearestNeighbor(CostMatrix*, Vertex, Tour*);


void doNearestNeighbor(CostMatrix *graph)
{
    auto tour = new Tour;
    Cost tourCost = nearestNeighbor(graph, Random()%dimGraph, tour);
    
    cerr << tourCost << endl;
    cout << tourCost << endl;

    delete tour;
}

Cost nearestNeighbor(CostMatrix *graph, Vertex initialVertex, Tour *tour)
{
    size_t dimGraph = graph->size();
    BoolVec visited(dimGraph, false);
    
    Vertex current, bestNext;
    vector<Vertex> candidateVertices;
    Cost bestCost, adjCost;
    
    tour->reserve(dimGraph);
    tour->push_back(initialVertex);
    visited[initialVertex] = true;
    
    
    // Construct the path
    for(size_t i=1; i<dimGraph; ++i) {
        current = tour->back();
        bestCost = oo_cost;

        // Search distance from nearest neighbor
        for(Vertex adj=0; (size_t)adj<dimGraph; ++adj) {
            adjCost = costEdge(current, adj);
            if(not visited[adj] and adjCost < bestCost) {
                bestCost = adjCost;
            }
        }

        // Choose as candidates those that have a distance good enough (i.e. dist(candidate) <= dist(nearest)*(1+EPS))
        candidateVertices = {};
        Cost candidateCost;
        for(Vertex candidate = 0; (size_t)candidate<dimGraph; ++candidate) {
            candidateCost = costEdge(current, candidate);
            if(not visited[candidate] and candidateCost <= bestCost * (1+nearestEPS)) {
                candidateVertices.push_back(candidate);
            }
        }

        // cadidateVertices contains the set of nearest neighbors of current, choose one at random
        bestNext = candidateVertices.at(rand() % candidateVertices.size());

        tour->push_back(bestNext);
        visited[bestNext] = true;

        current = bestNext;

    }

    return tourWeight(graph, tour);
}