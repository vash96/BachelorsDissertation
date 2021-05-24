#ifndef UPDATE_CANDIDATE_SET
#define UPDATE_CANDIDATE_SET

#include "lkhLib.cpp"

void updateCandidateSet(LKHNode*, LKHNode*, Cost);

// Add the candidate in the candidateSet (sorted ascending by alpha) only if |candidateSet| <= maxCandidates
void updateCandidateSet(LKHNode *node, LKHNode *candidate, Cost alpha)
{
    size_t cnt = 0;
    auto candidateSet = node->candidateSet;
    auto current = candidateSet;
    auto old = current;

    if(candidateSet == nullptr) {
        node->candidateSet = candidateSet = new Candidate;
        node->nCandidates = cnt = 1;
        candidateSet->adj = candidate;
        candidateSet->alpha = alpha;
        candidateSet->suc = nullptr;

        return;

    }else if(old->alpha > alpha) { // Head update
        current = new Candidate;
        current->adj = candidate;
        current->alpha = alpha;
        current->suc = candidateSet;
        node->candidateSet = old = current;
        node->nCandidates++;
    }else {
        // Search the right position in the middle of the list
        current = current->suc;
        cnt = 1;
        while(current != nullptr and current->alpha <= alpha) {
            old = current;
            current = current->suc;
            ++cnt;
        }

        if(current == nullptr) { // Tail update
            current = old->suc = new Candidate;
            current->adj = candidate;
            current->alpha = alpha;
            current->suc = nullptr;
        }else { // Strict middle update
            old->suc = new Candidate;
            old->suc->adj = candidate;
            old->suc->alpha = alpha;
            old->suc->suc = current;
            old = old->suc;
        }

        node->nCandidates++;
    }

    while(current->suc != nullptr) {
        old = current;
        current = current->suc;
    }

    if(node->nCandidates > maxCandidates and not adjusting) {
        delete current;
        old->suc = nullptr;

        node->nCandidates--;
    }
}

#endif