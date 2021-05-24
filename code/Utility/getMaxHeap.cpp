#ifndef GET_MAX_HEAP
#define GET_MAX_HEAP

#include "types.cpp"
#include "constants.cpp"

using namespace std;

MaxHeap* getMaxHeap(int, int, Cost, CostMatrix*, Tour*);
void collectElements(int, int, Cost, vector<HeapElement>&, CostMatrix*, Tour*);

inline Cost fun(int scheme, int j, Position & x, Position & y, CostMatrix* graph, Tour *tour)
{
    switch(scheme) {
        case 0:
            if(j==0) {
                return f11(x,y,graph,tour);
            }else if(j==1) {
                return f12(x,y,graph,tour);
            }else {
                return f13(x,y,graph,tour);
            }
            break;
        
        case 1:
            if(j==0) {
                return f21(x,y,graph,tour);
            }else if(j==1) {
                return f22(x,y,graph,tour);
            }else {
                return f23(x,y,graph,tour);
            }
            break;

        case 2:
            if(j==0) {
                return f31(x,y,graph,tour);
            }else if(j==1) {
                return f32(x,y,graph,tour);
            }else {
                return f33(x,y,graph,tour);
            }
            break;

        case 3:
            if(j==0) {
                return f41(x,y,graph,tour);
            }else if(j==1) {
                return f42(x,y,graph,tour);
            }else {
                return f43(x,y,graph,tour);
            }
            break;
    }

    return 0;
}

MaxHeap* getMaxHeap(int scheme, int j, Cost V, CostMatrix *graph, Tour *tour)
{
    vector<HeapElement> heapElements;
    heapElements.reserve(dimGraph * dimGraph);

    // Collect all elements from S_ab (with respect to the j-th f) and with 3*f>V
    collectElements(scheme, j, V, heapElements, graph, tour);

    // Make the heap from the collected elements, ordered by operator< in HeapElement{}
    auto maxHeap = new MaxHeap(heapElements.begin(), heapElements.end());

    return maxHeap;
}

void collectElements(int scheme, int j, Cost V, vector<HeapElement> & heapElements, CostMatrix *graph, Tour *tour)
{
    if(j<0 or j>2) {
        cerr << "Problem in getMaxHeap.collectElemenets\n";
        abort();
    }


    Cost fValue;
    for(Position x=0+2*(j==1); (size_t)x<dimGraph; ++x) {
        for(Position y=x+2+2*(j==2); (size_t)y+2*(j==0)<dimGraph; ++y) {
            fValue = fun(scheme, j, x, y, graph, tour);

            if(3*fValue > V) {
                heapElements.emplace_back(x, y, fValue);
            }
        }
    }
}

#endif