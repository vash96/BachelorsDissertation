#ifndef MAKE_2OPT
#define MAKE_2OPT

#include "lkhLib.cpp"

using namespace std;

void make2opt(LKHNode*,LKHNode*,LKHNode*,LKHNode*);

void make2opt(LKHNode *t1, LKHNode *t2, LKHNode *t3, LKHNode *t4)
{
    bool preP=true, postP=true;

    if(t1->suc != t2) {
        swap(t1, t2);
        swap(t3, t4);
    }

    auto r1 = t4, r2 = t2;
    Position pos = t1->pos;
    do {
        r1->pos = (++pos) % dimGraph;
        swap(r1->suc, r1->pre);
    }while((r1 = r1->suc) != r2);

    t2->pos = (++pos) % dimGraph;
    (t4->pre = t1)->suc = t4;
    t2->pre = t2->suc;
    (t2->suc = t3)->pre = t2;

    LKHNode *t[4] = {t1,t2,t3,t4};
    for(int i=0; i<4; ++i) {
        (*fixedEdge)[t[i]->id][t[(i+1)%4]->id] =
        (*fixedEdge)[t[(i+1)%4]->id][t[i]->id] = true;
    }

    if(not restoring) {
        moves.emplace(t1, t2, t3, t4);
    }
}


#endif