#include <bits/stdc++.h>
#include "../Utility/thesis.hpp"
using namespace std;

void doNearestInsertion(CostMatrix*);
Cost nearestInsertion(CostMatrix*, Vertex, Tour*&);
Cost updateTour(CostMatrix*, Vertex, TourList*);

void doNearestInsertion(CostMatrix *graph)
{
    Tour* tour = nullptr;
    Cost tourCost = nearestInsertion(graph, Random()%dimGraph, tour);

    cerr << tourCost << endl;
    cout << tourCost << endl;
    
    delete tour;
}

Cost nearestInsertion(CostMatrix *graph, Vertex initialVertex, Tour* & tour)
{
    size_t dimGraph = graph->size();
    vector<Cost> distance(dimGraph, oo_cost);
    BoolVec visited(dimGraph, false);
    auto tourList = new TourList;

    Cost bestCost;
    Vertex bestNext;
    vector<Vertex> candidateVertices;

    distance[initialVertex] = 0.0;
    for(size_t i=0; i<dimGraph; ++i) {
        bestCost = oo_cost;

        // Choose nearest vertex
        for(Vertex v=0; (size_t)v<dimGraph; ++v) {
            if(not visited[v] and distance[v] < bestCost) {
                bestCost = distance[v];
                bestNext = v;
            }
        }
        
        // Choose as candidates those that have a distance good enough (i.e. dist(candidate) <= dist(nearest)*(1+EPS))
        candidateVertices = {};
        Cost candidateCost;
        for(Vertex candidate = 0; (size_t)candidate<dimGraph; ++candidate) {
            candidateCost = distance[candidate];
            if(not visited[candidate] and candidateCost <= bestCost * (1+nearestEPS)) {
                candidateVertices.push_back(candidate);
            }
        }

        // Choose one at random and add it in the "right" position (with respect to NearestInsertion policy)
        bestNext = candidateVertices.at(rand() % candidateVertices.size());
        visited[bestNext] = true;
        updateTour(graph, bestNext, tourList);

        // Update distances from tour
        for(Vertex v=0; (size_t)v<dimGraph; ++v) {
            if(not visited[v]) {
                distance[v] = min(distance[v], costEdge(v, bestNext));
            }
        }
    }

    // Once we have the complete TourList, convertit to a Tour
    tour = fromListToTour(tourList);

    delete tourList;

    return tourWeight(graph, tour);
}

Cost updateTour(CostMatrix *graph, Vertex v, TourList *tour)
{
    if(tour->empty()) {
        tour->push_back(v);
        return 0.0;
    }

    auto it = tour->begin();
    auto bestIt = it;
    Cost bestCost = oo_cost, cost;
    Vertex i = tour->back(), j = tour->front();

    for(; it != tour->end(); ) {
        // Cost of inserting v between i--j
        cost = costEdge(i, v) + costEdge(v, j) - costEdge(i, j);
        if(cost < bestCost) {
            bestCost = cost;
            bestIt = it;
        }

        // Next pair
        i = j;
        if(it != tour->end()) {
            ++it;
            j = *it;
        }
    }

    // bestIt is the best position where to insert v
    tour->insert(bestIt, v);

    return bestCost;
}