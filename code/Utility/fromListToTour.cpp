#ifndef FROM_LIST_TO_TOUR
#define FROM_LIST_TO_TOUR

#include "constants.cpp"
#include "types.cpp"

Tour* fromListToTour(TourList*);

Tour* fromListToTour(TourList *tourList)
{
    auto tour = new Tour;
    tour->reserve(tourList->size()+1);
    tour->insert(tour->begin(), tourList->begin(), tourList->end());
    
    return tour;
}

#endif