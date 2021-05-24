#ifndef GENERATE_CANDIDATES
#define GENERATE_CANDIDATES

#include "types.cpp"
#include "constants.cpp"
#include "lkhLib.cpp"
#include "updateCandidateSet.cpp"

using namespace std;

void generateCandidates();

void generateCandidates()
{
    LKHNode *from, *to;

    from = firstNode;
    do {
        from->mark = nullptr;
    }while((from = from->suc) != firstNode);

    // For each vertex we want to compute alpha value
    from = firstNode;
    do {
        from->beta = -oo_cost;
        from->candidateSet = nullptr;
        // First, compute beta values of vertices in the path root->from
        if(from != firstNode) {
            for(to = from; to->dad != nullptr; to = to->dad) {
                to->dad->beta = max(to->beta, to->cost);
                to->dad->mark = from;
            }
        }

        // Next, compute beta for all other vertices
        for(to = firstNode->suc; to->suc != firstNode; to = to->suc) {
            if(to != from and to->mark != from) {
                if(from->dad == to or from->specialDad == to) {
                    // Case 1: {from, to} is in the 1-Tree
                    to->beta = 0.0;
                }else if(from == specialNode or to == specialNode) {
                    // Case 2: {from, to} is incident to specialNode (but not in the 1-Tree)
                    to->beta = max(specialNode->cost, specialNode->specialCost);
                }else {
                    // Case 3: inductively compute beta(from, to)
                    to->beta = max(to->dad->beta, costWithPenalty(from, to));
                    to->mark = from;
                }
            }
        }

        // Here we have all beta values update for {from, something}, we can now compute alpha and update candidateSet(from)
        for(to = firstNode; to->suc != firstNode; to = to->suc) {
            if(to != from) {
                updateCandidateSet(from, to, costWithPenalty(from, to) - to->beta);
            }
        }

    }while((from = from->suc) != firstNode);

    cerr << "Candidates generated succesfuly!\n";
}


#endif