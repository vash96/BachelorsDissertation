#ifndef FIND_TOUR
#define FIND_TOUR

#include "constants.cpp"
#include "types.cpp"
#include "lkhLib.cpp"
#include "chooseInitialTour.cpp"
#include "linKernighan.cpp"
#include "record.cpp"
#include "adjustCandidateSet.cpp"

using namespace std;

Cost findTour();

Cost findTour()
{
    size_t trial;
    Cost bestCost = oo_cost, cost;

    for(trial=0; trial<maxTrials; ++trial) {
        cerr << "Trial " << trial << endl;
        chooseInitialTour();
        cost = linKernighan();
        if(cost < bestCost) {
            bestCost = cost;
            recordBetterTour();
            adjustCandidateSet();
        }
    }

    resetCandidateSet();
    return bestCost;
}

#endif