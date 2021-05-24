#ifndef BEST_MOVE
#define BEST_MOVE

#include "lkhLib.cpp"
#include "make2opt.cpp"
#include "make3opt.cpp"

using namespace std;

LKHNode* bestMove(LKHNode*, LKHNode*, Cost*, Cost*);

/** Try to find a r-opt move (r<=3) which improves the actual tour (in that case, return nullptr),
 * otherwise apply the best (i.e. with maximum gain) 3opt move and return a pointer to the
 * last vertex touched by the move.
 **/
LKHNode* bestMove(LKHNode *t1, LKHNode *t2, Cost *g0, Cost *gain)
{
    *gain = 0;

    int case6, bestCase6;
    Cost g1, g2, g3, g4, best3opt = -oo_cost;
    LKHNode *T3, *T4, *T5, *T6;
    T3 = T4 = T5 = T6 = nullptr;

    orientation = (t1->suc == t2);

    // Search in t2 candidate set if there exist a suitable vertex
    for(auto candidate = t2->candidateSet; candidate != nullptr; candidate = candidate->suc) {
        auto t3 = candidate->adj;

        if(t3 == t1 or t3 == t2->pre or t3 == t2->suc or (*fixedEdge)[t2->id][t3->id] or
            (g1 = *g0 - costEdge(t2->id, t3->id)) <= 0) { // Last is the "positive gain criterion"
            continue;
        }

        // Try both alternatives for t4 (x4==0 -> cross t1,4, t2,3, otherwise two bridges t1,4 t2,3)
        for(int x4=0; x4<=1; ++x4) {
            auto t4 = (x4==0) ? Pre(t3) : Suc(t3);

            if(t4 == t1 or t4 == t2 or (*fixedEdge)[t3->id][t4->id]) {
                continue;
            }

            g2 = g1 + costEdge(t3->id, t4->id);
            if((*gain = g2 - costEdge(t4->id, t1->id))>0 and (not (*fixedEdge)[t1->id][t4->id]) and Suc(t4)!=t1 and x4==0) { // 2opt improving
                make2opt(t1, t2, t3, t4);
                return nullptr;
            }

            // Search in t4 candidate set if there exist a suitable vertex
            for(auto candidate2 = t4->candidateSet; candidate2 != nullptr; candidate2 = candidate2->suc) {
                auto t5 = candidate2->adj;
                LKHNode *t6 = nullptr;

                if(t5 == t4->pre or t5 == t4->suc or t5 == t1 or t5 == t2 or t5 == t3) {
                    continue;
                }

                if((*fixedEdge)[t4->id][t5->id] or (g3 = g2 - costEdge(t4->id, t5->id)) <= 0) {
                    continue;
                }

                case6 = 0;
                for(int x6=0; x6<=1; ++x6) {
                    if(x4 == 0) { // Cross
                        if(between(t2,t5,t4)) {
                            t6 = Suc(t5);
                            case6 = 0;
                        }else {
                            t6 = Pre(t5);
                            case6 = 1;
                        }
                    }else if(between(t2,t5,t3)) { // Bridge ok
                        if(x6 == 0) {
                            t6 = Pre(t5);
                            case6 = 2;
                        }else {
                            t6 = Suc(t5);
                            case6 = 3;
                        }
                    }else { // Bridge not ok
                        continue;
                    }

                    if(t6 == t1 or t6 == t2 or t6 == t3 or t6 == t4) {
                        continue;
                    }
                    if((*fixedEdge)[t5->id][t6->id]) {
                        continue;
                    }

                    g4 = g3 + costEdge(t5->id, t6->id);

                    if((*gain = g4 - costEdge(t6->id, t1->id)) > 0 and (not (*fixedEdge)[t6->id][t1->id])) { // 3opt improving
                        make3opt(t1,t2,t3,t4,t5,t6,case6);
                        return nullptr;
                    }

                    if(g4 > best3opt) { // Best 3opt found so far
                        best3opt = *gain;
                        bestCase6 = case6;
                        T3 = t3;
                        T4 = t4;
                        T5 = t5;
                        T6 = t6;
                    }
                }
            }
        }
    }

    *gain = 0;
    if(T6 != nullptr) { // Try the best move found so far (if it exists)
        *g0 = best3opt;
        make3opt(t1,t2,T3,T4,T5,T6,bestCase6);
    }

    return T6;
}

#endif