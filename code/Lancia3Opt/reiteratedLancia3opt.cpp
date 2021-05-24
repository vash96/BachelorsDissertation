#include <bits/stdc++.h>
#include "../Utility/thesis.hpp"

using namespace std;

void reiteratedLancia3opt(CostMatrix*);
void makeExchanges(Tour*, Permutation*);

void reiteratedLancia3opt(CostMatrix *graph)
{
    int oldMaxInteration = maxIteration;

    auto x = christofidesTour(graph);
    auto tour = x.first;
    auto perm = x.second;

    int numOfBest = 0;
    Cost bestCost = oo_cost;
    for(int i=0; i<maxIteration; ++i) {
        cerr << "Iteration " << (i+1) << endl;

        step = 1;
        ssstep = 1;
        while(bestImprovement(graph, tour, perm));

        // Found local minimum, save best and exchange some vertices
        Cost weight = tourWeight(graph, tour);
        
        if(weight + minDifference < bestCost) {
            bestCost = weight;
            ++numOfBest;
            ++maxIteration;
        }

        makeExchanges(tour, perm);
    }

    cerr << "Number of NEW absolute bests = " << numOfBest << endl;
    cerr << "Absolute best = " << bestCost << endl << endl;

    cout << numOfBest << endl;
    cout << bestCost << endl;

    maxIteration = oldMaxInteration;
}

void makeExchanges(Tour *tour, Permutation *perm)
{
    for(int i=0; i<maxExchanges; ++i) {
        int x = Random()%tour->size();
        int y = Random()%tour->size();

        swap(perm->at(tour->at(x)), perm->at(tour->at(y)));
        swap(tour->at(x), tour->at(y));
    }
}