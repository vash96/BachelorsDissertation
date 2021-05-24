#ifndef UTIL_PRIM
#define UTIL_PRIM

#include "types.cpp"
#include "constants.cpp"
#include <utility> // pair<>
#include "lkhLib.cpp"
using namespace std;

size_t CONTA = 0;

pair<Graph*, Cost> primMst(CostMatrix*, Vertex);
Cost primLKH();
void updateTopoSort(LKHNode*, LKHNode*);

pair<Graph*, Cost> primMst(CostMatrix *graph, Vertex initialVertex)
{
    size_t dimGraph = graph->size();
    auto mst = new Graph(dimGraph);

    vector<Cost> distance((*graph)[initialVertex].begin(), (*graph)[initialVertex].end());
    vector<Vertex> parent(dimGraph, initialVertex);
    BoolVec visited(dimGraph, false); visited[initialVertex] = true;
    Cost mstWeight = 0.0, bestCost;
    Vertex bestNext, parentNext;

    for(size_t i=1; i<dimGraph; ++i) {
        bestCost = oo_cost;

        // Search the closest vertex over the cut
        for(Vertex v=0; (size_t)v<dimGraph; ++v) {
            if(not visited[v] and distance[v]<bestCost) {
                bestCost = distance[v];
                bestNext = v;
                parentNext = parent[v];
            }
        }

        // Add it to MST
        (*mst)[bestNext].push_back(parentNext);
        (*mst)[parentNext].push_back(bestNext);
        mstWeight += bestCost;
        visited[bestNext] = true;

        // Update info for over the cut vertices
        for(Vertex v=0; (size_t)v<dimGraph; ++v) {
            if(costEdge(v, bestNext) < distance[v]) {
                distance[v] = costEdge(v, bestNext);
                parent[v] = bestNext;
            }
        }
    }


    return {mst, mstWeight};
}

Cost primLKH()
{
    LKHNode *current = firstNode->suc, *lastAdded = firstNode, *next;
    Cost weight  = 0.0, bestCost;

    do {        
        current->cost = costWithPenalty(firstNode, current);
        current->dad  = firstNode;
    }while((current = current->suc) != firstNode);
    firstNode->cost = 0.0;
    firstNode->dad = nullptr;

    for(size_t i=1; i<dimGraph; ++i) {
        bestCost = oo_cost;
        current  = lastAdded->suc;
        
        do { // Search for the closest vertex over the cut
            if(current->cost < bestCost) {
                bestCost = current->cost;
                next = current;
            }
        }while((current = current->suc) != firstNode);

        // next is the closest over the cut
        weight += next->cost;

        updateTopoSort(lastAdded, next);
        
        lastAdded = next;
        current = lastAdded->suc;
        while(current != firstNode) {
            if(costWithPenalty(lastAdded, current) < current->cost) {
                current->cost = costWithPenalty(lastAdded, current);
                current->dad  = lastAdded;
            }
            current = current->suc;
        }

        lastAdded->pos = (lastAdded->pre->pos + 1)%dimGraph;
    }
    firstNode->pre->pos = (firstNode->pos-1+dimGraph) % dimGraph;

    return weight;
}


// Make snd follow fst without interrupting the cycle
void updateTopoSort(LKHNode *fst, LKHNode *snd)
{
    if(fst->suc != snd) {
        follow(fst, snd);
    }
}


#endif