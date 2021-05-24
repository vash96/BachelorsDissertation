#ifndef MINIMUM_1_TREE_COST
#define MINIMUM_1_TREE_COST

#include "types.cpp"
#include "constants.cpp"
#include "prim.cpp"

using namespace std;

Cost minimum1TreeCost();

Cost minimum1TreeCost()
{
    Cost weight = primLKH();
    Cost sumPi = 0.0;

    auto current = firstNode;
    // Update isLeaf info
    do {
        current->isLeaf = true;
        current->v = -2;
        sumPi += current->currentPi;
    }while((current = current->suc) != firstNode);
    do {
        if(current->dad) {
            current->dad->v++;
            current->v++;
            if(current->dad->v >=0 ) {
                current->dad->isLeaf = false;
            }
        }

    }while((current = current->suc) != firstNode);

    // Search for max distance leaf
    Cost maxDist = -oo_cost;
    LKHNode *leaf;
    size_t i=0, j;
    for(auto node1 = firstNode; i<dimGraph; node1 = node1->suc, ++i) {
        if(not node1->isLeaf) {
            continue;
        }
        j = 0;
        Cost nearestCost = oo_cost;
        LKHNode *nearest;
        for(auto node2 = firstNode; j<dimGraph; node2 = node2->suc, ++j) {
            if(node2 != node1 and node2 != node1->dad and node1 != node2->dad and costWithPenalty(node1, node2) < nearestCost) {
                nearestCost = costWithPenalty(node1, node2);
                nearest = node2;
            }
        }

        if(nearestCost > maxDist) {
            maxDist = nearestCost;
            leaf = node1;
            leaf->specialCost = maxDist;
            leaf->specialDad = nearest;
        }
    }

    weight += maxDist;
    leaf->v++;
    leaf->specialDad->v++;

    // update norm
    treeNorm = 0;
    current = firstNode;
    do {
        treeNorm += (current->v) * (current->v);
    }while((current = current->suc) != firstNode);

    // We have to remember that leaf1 is the "special" node
    specialNode = leaf;

    return weight - 2*sumPi;
}

#endif