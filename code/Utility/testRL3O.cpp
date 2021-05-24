#ifndef TEST_RL3O
#define TEST_RL3O

#include "thesis.hpp"
#include "../Lancia3Opt/reiteratedLancia3opt.cpp"

int main()
{
    // To speedup the reading/writing with cin/cout to be roughly the same as of scanf/printf
    ios_base::sync_with_stdio(false);
    cout.precision(10);
    cout << fixed;

    auto SEED = chrono::system_clock::now().time_since_epoch().count();
    Random = minstd_rand0(SEED);

    for(int i=0; i<1000; ++i, Random());

    string input = "../input/custom/custom1000";
    freopen(input.data(), "r", stdin);
    auto graph = readInput();

    // int dim[4] = {1,2,3,5};
    for(int customEx=1; customEx<=10; ++customEx) {
        for(int i=0; i<1; i++) {
            string output = "../output/custom/RL3O/custom1000_ex" + to_string(customEx);
            freopen(output.data(), "w", stdout);

            cerr << "Executing Lancia 3-OPT with Reiteration on custom1000 with " << customEx << " exchanges.\n";
            cerr << "Tour cost is: ";

            maxExchanges = customEx;
            Time t = measureTime(reiteratedLancia3opt, graph);

            cerr << "Execution time is: " << t << endl << endl;
            cout << t << endl;
        }
    }
}

#endif