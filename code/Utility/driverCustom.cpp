#include <bits/stdc++.h>
#include "thesis.hpp"
using namespace std;

int main(int argc, char **argv)
{
    dimGraph = atoi(argv[1]);
    auto graph = new CostMatrix(dimGraph, vector<Cost>(dimGraph, 0));

    for(Vertex u=0; u<dimGraph; ++u) {
        for(Vertex v=u+1; v<dimGraph; ++v) {
            (*graph)[u][v] = (*graph)[v][u] = Random()%(dimGraph * dimGraph)+1;
        }
    }

    auto tour = new Tour(dimGraph);
    auto perm = new Permutation(dimGraph);
    for(Vertex v=0; v<dimGraph; ++v) {
        (*tour)[v] = v;
    }
    random_shuffle(tour->begin(), tour->end(), functionForShuffling);
    for(Vertex v=0; v<dimGraph; ++v) {
        (*perm)[(*tour)[v]] = v;
    }

    while(bestImprovement(graph, tour, perm)) {
        ++step;
        ++ssstep;
    }

    cout << "Step: " << step << endl;
    cout << "Avg: " << avg << endl << endl;

    delete tour;
    delete graph;

    return 0;
}