#ifndef RANDOM_COST_MATRIX
#define RANDOM_COST_MATRIX

#include "constants.cpp"
#include "types.cpp"
#include <algorithm>
#include <random>

using namespace std;

// Generate a random cost matrix with cost uniformly distributed in [1, dim*dim]
CostMatrix* randomCostMatrix(int);

CostMatrix* randomCostMatrix(int dim)
{
    auto mtx = new CostMatrix(dim, vector<Cost>(dim, 0.0));

    vector<double> costs(dim*dim);
    for(int i=0; i<dim*dim; ++i) {
        costs[i] = ((double)i+1)/(dim*dim);
    }

    random_shuffle(costs.begin(), costs.end(), functionForShuffling);
    
    for(int i=0; i<dim; ++i) {
        for(int j=i+1; j<dim; ++j) {
            (*mtx)[i][j] =
            (*mtx)[j][i] = costs[i*dim+j];
        }
    }

    return mtx;
}

#endif