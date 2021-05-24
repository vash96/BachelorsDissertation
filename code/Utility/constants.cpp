#ifndef UTIL_CONSTANTS
#define UTIL_CONSTANTS

#include "types.cpp"
#include <limits> // Numeric_limits ("infinity")

#include <random> // Linear congruential generator
#include <chrono> // Time for seeding the PRNG

size_t dimGraph;

CostMatrix *alpha;

int maxIteration = 20;
int maxExchanges = 10;



Cost nearestEPS = 0.05;
Cost minDifference = 0.01;

const Cost oo_cost = std::numeric_limits<Cost>::max();
const ReinsertionScheme r[4] = {
    {+3, +2},
    {-2, -3},
    {+3, -2},
    {-3, +2}
};




// Functions to be used in Lancia3Opt

inline Cost f11(Position & x, Position & y, CostMatrix* & graph, Tour* & tour) { return tauPlus(x,y); }
inline Cost f12(Position & x, Position & y, CostMatrix* & graph, Tour* & tour) { return tauPlus(x,y); }
inline Cost f13(Position & x, Position & y, CostMatrix* & graph, Tour* & tour) { return tauPlus(y,x); }

inline Cost f21(Position & x, Position & y, CostMatrix* & graph, Tour* & tour) { return tauPlus(x,pred(y)); }
inline Cost f22(Position & x, Position & y, CostMatrix* & graph, Tour* & tour) { return tauMins(succ(x),succ(succ(y))); }
inline Cost f23(Position & x, Position & y, CostMatrix* & graph, Tour* & tour) { return tauPlus(y,x); }

inline Cost f31(Position & x, Position & y, CostMatrix* & graph, Tour* & tour) { return tauPlus(x,y); }
inline Cost f32(Position & x, Position & y, CostMatrix* & graph, Tour* & tour) { return tauPlus(x,pred(y)); }
inline Cost f33(Position & x, Position & y, CostMatrix* & graph, Tour* & tour) { return tauMins(succ(y),succ(succ(x))); }

inline Cost f41(Position & x, Position & y, CostMatrix* & graph, Tour* & tour) { return tauMins(succ(x),succ(succ(y))); }
inline Cost f42(Position & x, Position & y, CostMatrix* & graph, Tour* & tour) { return tauPlus(x,y); }
inline Cost f43(Position & x, Position & y, CostMatrix* & graph, Tour* & tour) { return tauPlus(y,pred(x)); }

// Collect all functions in a 4 by 3 matrix: F[i][j] means the j-th function of the i-th scheme (starting from 0)

function<Cost(Position&, Position&, CostMatrix*&, Tour*&)> F[4][3] = {
    {f11, f12, f13},
    {f21, f22, f23},
    {f31, f32, f33},
    {f41, f42, f43}
};


#endif