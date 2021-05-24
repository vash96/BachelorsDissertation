#ifndef MAKE_NODE_SET
#define MAKE_NODE_SET

#include "types.cpp"
#include "constants.cpp"

using namespace std;

LKHNode* makeNodeSet();

LKHNode* makeNodeSet()
{
    auto start = new LKHNode;
    LKHNode *end = start, *old = nullptr;

    while(dimGraph--) {
        start->id = start->pos = dimGraph;
        start->suc = old;
        if(old) {
            old->pre = start;
        }

        old = start;

        if(dimGraph > 0) {
            start = new LKHNode;
        }
    }

    start->pre = end;
    end->suc = start;

    return start;
}

#endif