#ifndef STORE
#define STORE

#include "lkhLib.cpp"
#include "make2opt.cpp"

using namespace std;

void storeTour(queue<LKHNode*>&, BoolVec&);
void restoreTour();

void storeTour(queue<LKHNode*> & activeVertices, BoolVec & isActive)
{
    Move currentMove;
    LKHNode *t[4];
    while(not moves.empty()) {
        currentMove = moves.top();
        moves.pop();

        t[0] = currentMove.t1;
        t[1] = currentMove.t2;
        t[2] = currentMove.t3;
        t[3] = currentMove.t4;

        for(int i=0; i<4; ++i) {
            (*fixedEdge)[t[i]->id][t[(i+1)%4]->id] =
            (*fixedEdge)[t[(i+1)%4]->id][t[i]->id] = false;

            if(not isActive[t[i]->id]) {
                isActive[t[i]->id] = true;
                activeVertices.push(t[i]);
            }
        }
    }
}

// Undone all moves tried
void restoreTour()
{
    restoring = true;

    Move currentMove;
    while(not moves.empty()) {
        currentMove = moves.top();
        moves.pop();

        make2opt(currentMove.t1, currentMove.t4, currentMove.t3, currentMove.t2);
    }

    restoring = false;
}

#endif