#ifndef TOUR_WEIGHT
#define TOUR_WEIGHT

#include "constants.cpp"
#include "types.cpp"

Cost tourWeight(CostMatrix*, Tour*);

Cost tourWeight(CostMatrix *graph, Tour *tour)
{
    Cost cost = 0.0;
    if(tour->size() > 2) {
        auto i = tour->begin();
        auto j = i; ++j;

        do {
            cost += costEdge(*i, *j);
            ++i; ++j;
        }while(j != tour->end());
    }

    return cost + costEdge(tour->front(), tour->back());
}

#endif