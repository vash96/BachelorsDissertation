#ifndef SHORTCUT_TOUR
#define SHORTCUT_TOUR

#include "types.cpp"

void shortcutTour(size_t, TourList*);

void shortcutTour(size_t dimGraph, TourList *eulerList)
{
    BoolVec took(dimGraph, false);

    for(auto it=eulerList->begin(); it!=eulerList->end(); ) {
        if(took[*it]) {
            it = eulerList->erase(it);
        }else {
            took[*it] = true;
            ++it;
        }
    }
}

#endif