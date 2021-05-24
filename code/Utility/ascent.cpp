#ifndef ASCENT
#define ASCENT

#include "types.cpp"
#include "constants.cpp"
#include "minimum1TreeCost.cpp"

using namespace std;

Cost ascent();

Cost ascent()
{
    Cost bestWeight, weight;
    LKHNode *current;
    Period period = initialPeriod = dimGraph / 5;
    bool initialPhase = true;

    // First 1-Tree
    bestWeight = weight = minimum1TreeCost();

    // Check for optimality of the tour
    if(treeNorm == 0) {
        return weight;
    }
    // Initialize
    current = firstNode;
    do {
        current->lastV = current->v;
        current->bestPi = current->currentPi;
    }while((current = current->suc) != firstNode);

    for(Real stepSize = initialStepSize; stepSize > 0.0; period /= 2, stepSize /= 2.0) {
        for(size_t p = 1; stepSize > 0 and p <= period; ++p) {
    
            // Initialize currentPi
            do {
                if(current->v != 0) {
                    current->currentPi += stepSize*(7*current->v + 3*current->lastV)/10.0;
                }
                current->lastV = current->v;
            }while((current = current->suc) != firstNode);
    
            // New 1-Tree from 
            weight = minimum1TreeCost();
            if(treeNorm == 0) {
                return weight;
            }

            // Better lowerbound
            if(weight > bestWeight + EPS) {
                bestWeight = weight;
    
                // Update all bestPi values
                do {
                    current->bestPi = current->currentPi;
                }while((current = current->suc) != firstNode);

                if(initialPhase) { stepSize *= 2.0; }
                if(p == period) { period *= 2; }
            }else if(initialPhase and p > initialPeriod/2) {
                initialPhase = false;
                p = 0;
                stepSize = 3.0*stepSize/4.0;
            }
        }
    }

    // If we are here, we have not found an optimal tour, and so just return the best lower_bound
    do {
        current->currentPi = current->bestPi;
    }while((current = current->suc) != firstNode);

    return minimum1TreeCost();
}

#endif