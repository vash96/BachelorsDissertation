#ifndef LIN_KERNIGHAN
#define LIN_KERNIGHAN

#include "lkhLib.cpp"
#include "store.cpp"
#include "bestMove.cpp"
#include "record.cpp"
using namespace std;

Cost linKernighan();

Cost linKernighan()
{
    Cost gain = 0.0, g = 0.0, tourCost = 0.0;
    fixedEdge = new BoolMatrix(dimGraph, BoolVec(dimGraph, false));
    queue<LKHNode*> activeVertices;
    BoolVec isActive(dimGraph, true);


    auto current = firstNode;
    // Compute cost of the tour
    do {
        tourCost += costEdge(current->id, current->suc->id);
        activeVertices.push(current);
    }while((current = current->suc) != firstNode);


    // While there are active vertices
    while(not activeVertices.empty()) {
        // For each choice for t2
        auto t1 = activeVertices.front();
        activeVertices.pop(); // De-activate t1
        isActive[t1->id] = false;

        for(int x1=0; x1<=1; ++x1) {
            auto t2 = x1==0 ? t1->pre : t1->suc;
    
            if((*fixedEdge)[t1->id][t2->id]) {
                continue;
            }

            g = costEdge(t1->id, t2->id);
            // Apply a chain of bestMoves
            while((t2 = bestMove(t1, t2, &g, &gain)) != nullptr);

            // If we've found an improvement, save it and make all vertices active again
            if(gain > 0) {
                tourCost -= gain;
                storeTour(activeVertices, isActive);

                break; // from for
            }else { // In case of no improvement, undo all moves
                restoreTour();
            }
        }
    }

    delete fixedEdge;
    return tourCost;
}

#endif