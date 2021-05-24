#ifndef CHOOSE_INITIAL_TOUR
#define CHOOSE_INITIAL_TOUR

#include "constants.cpp"
#include "types.cpp"
#include "lkhLib.cpp"
#include "../Utility/christofides.cpp"

using namespace std;

void chooseInitialTour();

void chooseInitialTour()
{
    auto tour = christofides(graph, Random()%dimGraph);
    LKHNode *current = firstNode, *lastAdded = nullptr;

    while(current->id != tour->front()) {
        current = current->suc;
    }

    // Now current is the "real" first node;
    Position pos = 0;
    current->pos = pos++;
    firstNode = lastAdded = current;
    for(auto v : *tour) {
        if(v != tour->front()) {
            for(current = lastAdded->suc; current->id != v; current = current->suc);
            
            // Current is the next to be added to the tour
            follow(lastAdded, current);
            lastAdded = current;
            lastAdded->pos = pos++;
        }
    }

    // Tour made
}

#endif