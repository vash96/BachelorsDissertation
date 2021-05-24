#ifndef ALLOCATE
#define ALLOCATE

#include "constants.cpp"
#include "types.cpp"
#include "lkhLib.cpp"

using namespace std;

void allocateStructures();
void deAllocateStructures();

void allocateStructures()
{
    firstNode = nodesBuffer = new LKHNode[dimGraph];
    
    for(size_t i=0; i<dimGraph; ++i) {
        firstNode[i].id = (firstId+i) % dimGraph;
        firstNode[i].suc = firstNode + (i+1)%dimGraph;
        firstNode[i].pre = firstNode + (i+dimGraph-1)%dimGraph;
        firstNode[i].currentPi = 0.0;
        firstNode[i].dad = nullptr;
        firstNode[i].candidateSet = nullptr;
        firstNode[i].nCandidates = 0;
        firstNode[i].v = firstNode[i].lastV = 0;
        firstNode[i].pos = i;
    }

    betterTour = new Tour(dimGraph, -1);
    bestTour = new Tour(dimGraph, -1);

    cerr << "Allocation succeed\n";
}

void deAllocateStructures()
{
    // Deleting candidates before nodes
    auto current = firstNode;
    do {
        auto candidate = current->candidateSet;
        auto old = candidate;
        while(candidate != nullptr) {
            candidate = candidate->suc;
            delete old;
            old = candidate;
        }
    }while((current = current->suc) != firstNode);

    delete [] nodesBuffer;
    delete betterTour;
    delete bestTour;

    cerr << "Deallocation succeed\n";
}

#endif