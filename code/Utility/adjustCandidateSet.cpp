#ifndef ADJUST_CANDIDATE_SET
#define ADJUST_CANDIDATE_SET

#include "lkhLib.cpp"
#include "updateCandidateSet.cpp"
#include "inBestTour.cpp"

using namespace std;

void adjustCandidateSet();
void resetCandidateSet();

void adjustCandidateSet()
{
    cerr << "Adjusting...\n";
    adjusting = true;

    int i=0;
    for(auto node = firstNode; i<dimGraph; ++i, node = node->suc) {
        // Search for {node, node->pre} in candidateSet(node)
        auto candidate = node->candidateSet;
        for(; candidate != nullptr and candidate->adj != node->pre; candidate = candidate->suc);

        if(candidate == nullptr) {
            updateCandidateSet(node, node->pre, inBestTour(node, node->suc) ? -oo_cost : oo_cost);
        }
    }

    adjusting = false;
}


// Just remove all candidates with alpha = +/-oo
void resetCandidateSet()
{
    cerr << "Resetting...\n";
    int i=0;
    for(auto node = firstNode; i<dimGraph; ++i, node = node->suc) {
        auto candidate = node->candidateSet;
        Candidate *last = nullptr;
        for(; candidate != nullptr; ) {
            if(candidate->alpha == -oo_cost or candidate->alpha == +oo_cost) {
                node->nCandidates--;
                if(last == nullptr) {
                    node->candidateSet = candidate->suc;
                    delete candidate;
                    candidate = node->candidateSet;
                }else {
                    last->suc = candidate->suc;
                    delete candidate;
                    candidate = last->suc;
                }
            }else {
                last = candidate;
                candidate = candidate->suc;
            }
        }
    }
}

#endif