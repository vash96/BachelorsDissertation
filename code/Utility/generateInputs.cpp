#ifndef GENERATE_INPUTS
#define GENERATE_INPUTS

#include "thesis.hpp"

using namespace std;

int main()
{
    auto SEED = chrono::system_clock::now().time_since_epoch().count();
    Random = minstd_rand0(SEED); // Seeding the generator
    for(int i=0; i<1000; ++i, Random());


    int dim[4] = {1, 2, 3, 5};

    for(int mul = 100; mul <= 1000; mul *= 10) {
        for(int i=0; i<4; ++i) {
            cerr << "Generating input custom" << (mul * dim[i]) << endl;


            int sizeGraph = dim[i] * mul;
            auto graph = randomCostMatrix(sizeGraph);
            assert(graph != nullptr);
            string filename = "../input/custom/new_custom" + to_string(sizeGraph);
            generateCustomInput(filename, graph);
        }
    }

    return 0;
}

#endif