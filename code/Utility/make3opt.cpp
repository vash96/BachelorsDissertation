#ifndef MAKE_3OPT
#define MAKE_3OPT

#include "lkhLib.cpp"
#include "make2opt.cpp"

using namespace std;

void make3opt(LKHNode*,LKHNode*,LKHNode*,LKHNode*,LKHNode*,LKHNode*,int);


void make3opt(LKHNode *t1, LKHNode *t2, LKHNode *t3, LKHNode *t4, LKHNode *t5, LKHNode *t6, int case3opt)
{
    switch(case3opt) {
        case 0:
            make2opt(t1,t2,t3,t4);
            make2opt(t5,t6,t1,t4);
            break;
        case 1:
            make3opt(t4,t3,t2,t1,t6,t5,0);
            break;
        case 2:
            make3opt(t3,t4,t5,t6,t1,t2,0);
            break;
        case 3:
            make2opt(t1,t2,t4,t3);
            make3opt(t3,t1,t6,t5,t4,t2,0);
            break;
        default:
            cerr << "Error in make3opt\n";
            abort();
    }
}

#endif