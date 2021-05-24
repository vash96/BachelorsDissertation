#ifndef THESIS_HPP
#define THESIS_HPP

#define costEdge(i, j) (*graph)[i][j]

#define succ(x) (x+1)%dimGraph
#define pred(x) (x-1+dimGraph)%dimGraph

#define tauPlus(a,b) costEdge((*tour)[a], (*tour)[succ(a)]) - costEdge((*tour)[a], (*tour)[succ(b)])
#define tauMins(a,b) costEdge((*tour)[a], (*tour)[pred(a)]) - costEdge((*tour)[a], (*tour)[pred(b)])

#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <functional>

#include "types.cpp"
#include "readInput.cpp"
#include "constants.cpp"
#include "prim.cpp"
#include "measureTime.cpp"
#include "generateCustomInput.cpp"
#include "randomCostMatrix.cpp"

//#include "inducedGraph.cpp"
#include "oddDegreeVertices.cpp"
#include "minimumWeightMatching.cpp"
#include "findEulerTour.cpp"
#include "fromListToTour.cpp"
#include "tourWeight.cpp"
#include "print.cpp"
#include "shortcutTour.cpp"
#include "randomTour.cpp"
#include "bestImprovement.cpp"
#include "christofides.cpp"

// LKH
#include "createCandidateSet.cpp"
#include "createCandidateSet.cpp"
#include "ascent.cpp"
#include "minimum1TreeCost.cpp"
#include "allocate.cpp"
#include "generateCandidates.cpp"
#include "findTour.cpp"
#include "chooseInitialTour.cpp"
#include "record.cpp"

#endif