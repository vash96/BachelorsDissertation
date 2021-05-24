#ifndef IN_BEST_TOUR
#define IN_BEST_TOUR

#include "lkhLib.cpp"

bool inBestTour(LKHNode*, LKHNode*);

bool inBestTour(LKHNode *x, LKHNode *y)
{
    for(size_t i=0; i<dimGraph-1; ++i) {
        if((x->id == (*bestTour)[i] and y->id == (*bestTour)[i+1]) or
            x->id == (*bestTour)[i+1] and y->id == (*bestTour)[i]) {
                return true;
        }
    }

    return false;
}

#endif