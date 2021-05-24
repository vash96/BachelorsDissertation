#ifndef MEASURE_TIME
#define MEASURE_TIME

#include <functional>
#include "constants.cpp"
#include "types.cpp"

using namespace std;

// Execute func and return execution time
Time measureTime(function<void(CostMatrix*)>, CostMatrix*);

Time measureTime(function<void(CostMatrix*)> fun, CostMatrix *input)
{
    Time t0 = clock();
    fun(input);
    Time t1 = clock();

    return (t1-t0) / CLOCKS_PER_SEC;
}

#endif