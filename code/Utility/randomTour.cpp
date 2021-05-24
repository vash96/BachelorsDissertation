#ifndef RANDOM_TOUR
#define RANDOM_TOUR

#include "constants.cpp"
#include "types.cpp"
#include "christofides.cpp"

#include <algorithm> // random_shuffle
using namespace std;

pair<Tour*, Permutation*> randomTour(CostMatrix*);
pair<Tour*, Permutation*> christofidesTour(CostMatrix*);

pair<Tour*, Permutation*> randomTour(CostMatrix* graph)
{
    auto tour = new Tour(dimGraph);
    for(Vertex v=0; (size_t)v<dimGraph; ++v) {
        (*tour)[v] = v;
    }

    random_shuffle(tour->begin(), tour->end(), functionForShuffling);

    auto perm = new Permutation(dimGraph);
    for(size_t i=0; i<dimGraph; ++i) {
        (*perm)[ (*tour)[i] ] = i;
    }

    return {tour, perm};
}

pair<Tour*, Permutation*> christofidesTour(CostMatrix *graph)
{
    auto tour = christofides(graph, Random()%dimGraph);
    auto perm = new Permutation(dimGraph);
    for(size_t i=0; i<dimGraph; ++i) {
        perm->at(tour->at(i)) = i;
    }

    return {tour, perm};
}

#endif