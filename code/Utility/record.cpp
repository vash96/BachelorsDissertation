#ifndef RECORD
#define RECORD

#include "lkhLib.cpp"

using namespace std;

void recordBetterTour();
void recordBestTour();

void recordBetterTour()
{
    auto current = firstNode;
    do {
        (*betterTour)[current->pos] = current->id;
    }while((current = current->suc) != firstNode);
}

void recordBestTour()
{
    auto current = firstNode;
    do {
        (*bestTour)[current->pos] = current->id;
    }while((current = current->suc) != firstNode);
}

#endif