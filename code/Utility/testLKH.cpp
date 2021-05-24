#ifndef TEST_LKH
#define TEST_LKH

#include "thesis.hpp"
#include "../LinKernighan/linKernighanHelsgaun.cpp"

int main(int argc, char **argv)
{
    if(argc < 3) {
        cerr << "Too few parameters.\n";
        return 0;
    }

    int lft = atoi(argv[1]);
    int rgt = atoi(argv[2]);

    // To speedup the reading/writing with cin/cout to be roughly the same as of scanf/printf
    ios_base::sync_with_stdio(false);
    cout.precision(10);
    cout << fixed;

    auto SEED = chrono::system_clock::now().time_since_epoch().count();
    Random = minstd_rand0(SEED);

    for(int i=0; i<1000; ++i, Random());

    string input = "../input/custom/new_custom5000";
    freopen(input.data(), "r", stdin);
    
    auto graph = readInput();

    for(int maxC = lft; maxC <= rgt; ++maxC) {
        maxCandidates = maxC;
        string output = "../output/custom/LKH/new_custom_cand" + to_string(maxC);

        freopen(output.data(), "w", stdout);

        cerr << "Executing Lin-Kernighan-Helsgaun on new_custom5000 with " << maxC << " max candidates.\n";
        cerr << "Tour cost is: ";

        Time t = measureTime(doLinKernighanHelsgaun, graph);

        cerr << "Execution time is: " << t << endl << endl;
        cout << t << endl;
    }
}

#endif