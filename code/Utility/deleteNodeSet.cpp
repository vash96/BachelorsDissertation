#ifndef DELETE_NODE_SET
#define DELETE_NODE_SET

#include "types.cpp"
#include "constants.cpp"
#include "lkhLib.cpp"

using namespace std;

void deleteNodeSet(LKHNode*);

void deleteNodeSet(LKHNode *start)
{
    auto next = start;
    while(next) {
        next = start->suc;
        delete start;
        start = next;
    }
}

#endif