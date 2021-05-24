#include <bits/stdc++.h>
#include "thesis.hpp"
#include "../NearestNeighbor/nnAlgo.cpp"
#include "../NearestInsertion/niAlgo.cpp"
#include "../Christofides/doChristofides.cpp"
#include "../Lancia3Opt/lancia3opt.cpp"
#include "../Lancia3Opt/reiteratedLancia3opt.cpp"
using namespace std;

typedef function<void(Graph*)> TspAlgorithm;

int main()
{
    auto SEED = chrono::system_clock::now().time_since_epoch().count();
    Random = minstd_rand0(SEED); // Seeding the generator

    cerr << "Seed = " << SEED << "\n";
    for(int i=0; i<10; ++i) {
        cerr << Random() << " ";
    }
    cerr << endl;

    for(int i=0; i<1000; ++i, Random());

    auto graph = readInput();

    cerr.precision(10);
    cerr << fixed;
    // auto t = measureTime(doNearestNeighbor, graph);
    // cerr << "Time is " << t << endl;

    auto t = measureTime(doLancia3OptRandom, graph);
    cerr << "Time for L3OC: " << t << endl;
    
    // doNearestNeighbor(graph);
    // doNearestInsertion(graph);
    // doChristofides(graph);
    // // doLancia3OptRandom(graph);
    // // doLancia3OptChristofides(graph);
    // // reiteratedLancia3opt(graph);


    delete graph;

    return 0;
}