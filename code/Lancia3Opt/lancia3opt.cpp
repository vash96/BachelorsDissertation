#include <bits/stdc++.h>
#include "../Utility/thesis.hpp"
using namespace std;

void doLancia3Opt(CostMatrix*,Tour*,Permutation*);
void doLancia3OptRandom(CostMatrix*);
void doLancia3OptChristofides(CostMatrix*);

void doLancia3OptRandom(CostMatrix *graph)
{
    auto x = randomTour(graph);
    auto tour = x.first;
    auto perm = x.second;

    doLancia3Opt(graph, tour, perm);
}

void doLancia3OptChristofides(CostMatrix *graph)
{
    auto x = christofidesTour(graph);
    auto tour = x.first;
    auto perm = x.second;

    doLancia3Opt(graph, tour, perm);
}


void doLancia3Opt(CostMatrix *graph, Tour *tour, Permutation *perm)
{
    step = 1;
    ssstep = 0;

    Cost lastCost = tourWeight(graph, tour);
    Cost newCost = oo_cost;
    while(bestImprovement(graph, tour, perm)) {
        newCost = tourWeight(graph, tour);
        assert(newCost < lastCost);
        if(abs(lastCost-newCost) <= minDifference) {
            break;
        }
        lastCost = newCost;
    }

    lastCost = min(lastCost, newCost);

    cerr << "Step: " << step << endl;
    cout << lastCost << endl;
    cout << step << endl;
    cout << avg << endl;

    delete tour;
    delete perm;
}
