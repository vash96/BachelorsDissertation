#include <bits/stdc++.h>
#include "../Utility/thesis.hpp"
#include "../Utility/lkhLib.cpp"
using namespace std;

void doLinKernighanHelsgaun(CostMatrix *graph)
{
    ::graph = graph;

    allocateStructures();
    auto heldKarp = createCandidateSet();

    Cost bestCost = oo_cost;
    for(size_t run=0; run<maxRuns; ++run) {
        cerr << "Run " << run << endl;

        Cost cost = findTour();
        if(cost < bestCost) {
            recordBestTour();
            bestCost = cost;
        }

        cerr << "Cost: " << cost << endl << endl;
    }

    cerr << "Tour cost: " << bestCost << endl;
    cout << bestCost << endl;
    cout << heldKarp << endl;
    // cout << "Tour found: ";
    // print(cout, bestTour);



    /**
     * Need to deallocate graph, nodes, candidateSets, fixedEdge, betterTour, bestTour
     **/

    deAllocateStructures();
}