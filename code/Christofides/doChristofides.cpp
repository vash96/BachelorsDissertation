#include <bits/stdc++.h>
#include "../Utility/thesis.hpp"
using namespace std;

void doChristofides(CostMatrix*);

void doChristofides(CostMatrix *graph)
{
    auto tour = christofides(graph, Random()%dimGraph);
    Cost tourCost = tourWeight(graph, tour);
    
    cerr << tourCost << endl;
    cout << tourCost << endl;

    delete tour;
}