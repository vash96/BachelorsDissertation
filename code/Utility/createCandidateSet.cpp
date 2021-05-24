#ifndef CREATE_CANDIDATE_SET
#define CREATE_CANDIDATE_SET

#include "types.cpp"
#include "constants.cpp"
#include "ascent.cpp"
#include "generateCandidates.cpp"

using namespace std;

Cost createCandidateSet();

Cost createCandidateSet()
{
    cerr << "Creating candidate set!\n";

    Cost heldKarp = ascent();
    cerr << "Held Karp bound: " << heldKarp << "\n";

    cerr << "Generating candidates...\n";
    generateCandidates();

    return heldKarp;
}

#endif