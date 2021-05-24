#ifndef BEST_IMPROVEMENT
#define BEST_IMPROVEMENT

#include "types.cpp"
#include "constants.cpp"
#include "getMaxHeap.cpp"
#include <chrono>

#define Now() chrono::system_clock::now()

size_t step = 1;
size_t ssstep = 0;
double avg = 8.5;

bool bestImprovement(CostMatrix*, Tour*, Permutation*);
bool applyMove(pair<int, vector<int>>&, Tour*);

bool bestImprovement(CostMatrix *graph, Tour *tour, Permutation *perm)
{
    auto t0 = chrono::system_clock::now();

    size_t n = 0;
    pair<int, vector<int>> insertionSet;
    Cost best = minDifference;

    int whichF[3] = {0,1,2};
    
    for(int scheme=0; scheme<4; ++scheme) { // For each reinsertion scheme
       
        for(int i=0; i<3; ++i) { // For each function fj
            int j = whichF[i];
            // Make the heap and search for improvements
            auto tt0 = Now();
            auto heap = getMaxHeap(scheme, j, best, graph, tour);
            auto tt1 = Now();
            chrono::duration<double> dur = tt1-tt0;

            cerr << "Time to make the heap: " << dur.count() << "s\n";
            n += heap->size();
            
            tt0 = Now();
            int ccccc=0;
            while(not heap->empty() and heap->top().fValue*3>best) {
                // Search for the third element
                auto head = heap->top(); heap->pop();
                Cost fValue = head.fValue;
                Position x = head.x;
                Position y = head.y;
            
                Position bestZ = -1;
                Cost bestZCost = -oo_cost;
                Cost currentZCost;

                switch(j) {
                    case 0:
                        for(Position z=y+2; (size_t)z+(x==0)<dimGraph; ++z) {
                            if(scheme==0) {
                                currentZCost = f12(y,z, graph, tour) + f13(x,z,graph, tour);
                            }else if(scheme==1) {
                                currentZCost = f22(y,z, graph, tour) + f23(x,z,graph, tour);
                            }else if(scheme==2) {
                                currentZCost = f32(y,z, graph, tour) + f33(x,z,graph, tour);
                            }else {
                                currentZCost = f42(y,z, graph, tour) + f43(x,z,graph, tour);
                            }
                            // currentZCost = F[scheme][1](y,z, graph, tour)+F[scheme][2](x,z, graph, tour);
                            if(currentZCost > bestZCost) {
                                bestZCost = currentZCost;
                                bestZ = z;
                            }
                        }
                        if(bestZCost+fValue > best) {
                            ccccc++;
                            insertionSet = {scheme, {x,y,bestZ}};
                            // insertionSet[0] = scheme;
                            // insertionSet[1] = x;
                            // insertionSet[2] = y;
                            // insertionSet[3] = bestZ;
                            best = bestZCost + fValue;
                        }
                        break;

                    case 1:
                        for(Position z=0; z<=x-2; ++z) {
                            if(scheme==0) {
                                currentZCost = f11(z,x, graph, tour) + f13(z,y,graph, tour);
                            }else if(scheme==1) {
                                currentZCost = f21(z,x, graph, tour) + f23(z,y,graph, tour);
                            }else if(scheme==2) {
                                currentZCost = f31(z,x, graph, tour) + f33(z,y,graph, tour);
                            }else {
                                currentZCost = f41(z,x, graph, tour) + f43(z,y,graph, tour);
                            }
                            // currentZCost = F[scheme][0](z,x, graph, tour)+F[scheme][2](z,y, graph, tour);
                            if(currentZCost > bestZCost) {
                                bestZCost = currentZCost;
                                bestZ = z;
                            }
                        }
                        if(bestZCost+fValue > best) {
                            ccccc++;
                            insertionSet = {scheme, {bestZ,x,y}};
                            // insertionSet[0] = scheme;
                            // insertionSet[2] = x;
                            // insertionSet[3] = y;
                            // insertionSet[1] = bestZ;
                            best = bestZCost + fValue;
                        }
                        break;

                    case 2:
                        for(Position z=x+2; z<=y-2; ++z) {
                            if(scheme==0) {
                                currentZCost = f11(x,z, graph, tour) + f12(z,y,graph, tour);
                            }else if(scheme==1) {
                                currentZCost = f21(x,z, graph, tour) + f22(z,y,graph, tour);
                            }else if(scheme==2) {
                                currentZCost = f31(x,z, graph, tour) + f32(z,y,graph, tour);
                            }else {
                                currentZCost = f41(x,z, graph, tour) + f42(z,y,graph, tour);
                            }
                            // currentZCost = F[scheme][0](x,z, graph, tour)+F[scheme][1](z,y, graph, tour);
                            if(currentZCost > bestZCost) {
                                bestZCost = currentZCost;
                                bestZ = z;
                            }
                        }
                        if(bestZCost+fValue > best) {
                            ccccc++;
                            insertionSet = {scheme, {x,bestZ,y}};
                            // insertionSet[0] = scheme;
                            // insertionSet[1] = x;
                            // insertionSet[3] = y;
                            // insertionSet[2] = bestZ;
                            best = bestZCost + fValue;
                        }
                        break;
                }
            }
            tt1 = Now();

            dur = tt1-tt0;
            cerr << "Time to find best selection: " << dur.count() << "s\n";
            cerr << "New best champions: " << ccccc << "\n";
            n -= heap->size();

            tt0 = Now();
            delete heap;
            tt1 = Now();
            dur = tt1-tt0;
            cerr << "Time to delete heap: " << dur.count() << "s\n\n";
        }
        
    }

    auto t1 = chrono::system_clock::now();
    chrono::duration<double> dur = t1-t0;

    cerr << "Time to find best selection: " << dur.count() << "s\n";

    if(step > 1) {
        avg = (avg*step+dur.count())/(step+1);
    }else {
        avg = dur.count();
    }
    if(ssstep % 20 == 0) {
        cerr << "Step " << step << endl;
        // cerr << "Avg n. of elements seen per queue: " << n/12 << endl;
        // cerr << "Time: " << (t1-t0)/CLOCKS_PER_SEC << endl;
        // cerr << "Avg time: " << avg << endl << endl;
    }

    ++step;
    ++ssstep;

    // apply the best improvement move and return
    t0 = chrono::system_clock::now();
    auto apll = applyMove(insertionSet, tour);
    t1 = chrono::system_clock::now();
    dur = t1-t0;

    cerr << "Time to apply best move: " << dur.count() << "s\n-----------------------------------------------------------------------------------------------------\n";
    return apll;
}

bool applyMove(pair<int,vector<int>> & insertionSet, Tour *tour)
{
    if(insertionSet.second.empty()) { // Improving move not found
        return false;
    }

    size_t dimGraph = tour->size();
    
    // Get i1, i2, i3
    Position *i = insertionSet.second.data(); // i = [i1, i2, i3]
    Tour seg1, seg2, seg3;
    seg1.reserve(dimGraph);
    seg2.reserve(dimGraph);
    seg3.reserve(dimGraph);

    // cout << "Done move with " << i[0] << " " << i[1] << " " << i[2] << endl;

    // To simplify segment selection, double the tour (to simulate circuit)
    tour->reserve(2*dimGraph);
    tour->insert(tour->end(), tour->begin(), tour->end());

    // Segment1 [i3 (+) 1, i1]
    seg1.insert(seg1.begin(), tour->begin()+i[2]+1, tour->begin()+i[0]+dimGraph+1);

    // Segment2 [i1 (+) 1, i2]
    seg2.insert(seg2.begin(), tour->begin()+i[0]+1, tour->begin()+i[1]+1);

    // Segment3 [i2 (+) 1, i3]
    seg3.insert(seg3.begin(), tour->begin()+i[1]+1, tour->begin()+i[2]+1);

    tour->clear();
    tour->reserve(dimGraph);


    tour->insert(tour->end(), seg1.begin(), seg1.end()); // +1
    switch(insertionSet.first) {
        case 0:
            tour->insert(tour->end(), seg3.begin(), seg3.end()); // +3

            tour->insert(tour->end(), seg2.begin(), seg2.end()); // +2
            break;

        case 1:
            reverse(seg2.begin(), seg2.end());
            tour->insert(tour->end(), seg2.begin(), seg2.end()); // -2

            reverse(seg3.begin(), seg3.end());
            tour->insert(tour->end(), seg3.begin(), seg3.end()); // -3
            break;

        case 2:
            tour->insert(tour->end(), seg3.begin(), seg3.end()); // +3

            reverse(seg2.begin(), seg2.end());
            tour->insert(tour->end(), seg2.begin(), seg2.end()); // -2
            break;
        
        case 3:
            reverse(seg3.begin(), seg3.end());
            tour->insert(tour->end(), seg3.begin(), seg3.end()); // -3

            tour->insert(tour->end(), seg2.begin(), seg2.end()); // +2
            break;
    }

    return true;
}

#endif