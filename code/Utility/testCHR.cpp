#ifndef TEST_CHR
#define TEST_CHR

#include "thesis.hpp"
#include "../Christofides/doChristofides.cpp"

int main()
{
    // To speedup the reading/writing with cin/cout to be roughly the same as of scanf/printf
    ios_base::sync_with_stdio(false);
    cout.precision(10);
    cout << fixed;

    auto SEED = chrono::system_clock::now().time_since_epoch().count();
    Random = minstd_rand0(SEED);

    for(int i=0; i<1000; ++i, Random());

    // a280  pr2392  pr439  rl5915  u1060  u1817  vm1748
    string files[5] = {
        "a280",
        "pr439",
        "u1060",
        "vm1748",
        "pr2392"
    };

    // int dim[4] = {1,2,3,5};
    for(int i=0; i<5; i++) {
        string input = "../input/tsplib/" + files[i];
        string output = "../output/tsplib/CHR/" + files[i];

        freopen(input.data(), "r", stdin);
        freopen(output.data(), "w", stdout);

        cerr << "Executing Christofides on " << files[i] << "\n";

        cerr << "Tour cost is: ";

        auto graph = readInput();
        Time t = measureTime(doChristofides, graph);

        cerr << "Execution time is: " << t << endl << endl;
        cout << t << endl;
    }
}

#endif