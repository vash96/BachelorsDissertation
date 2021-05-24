#ifndef LKH_LIB
#define LKH_LIB

#include "constants.cpp"
#include "types.cpp"

#define penalty(i,j) (i->currentPi + j->currentPi)
#define costWithPenalty(i,j) (costEdge(i->id, j->id) + (i != j ? penalty(i,j) : 0))
#define Pre(x) (orientation ? x->pre : x->suc)
#define Suc(x) (orientation ? x->suc : x->pre)

using namespace std;

typedef size_t Norm;
typedef size_t Period;
typedef struct LKHNode LKHNode;
typedef struct Candidate Candidate;
typedef struct Move Move;

struct LKHNode {
    int nCandidates; // How many candidates are in this->candidateSet
    bool isLeaf;
    bool visited;
    Vertex id;
    Position pos;
    int v;       // degree - 2 (in MST)
    int lastV;   // v at the previous step of ascent
    Cost cost;      // Cost of the edge {Dad, this}
    Cost specialCost;
    Cost currentPi, bestPi;
    Cost beta;
    LKHNode* suc;
    LKHNode* pre;
    LKHNode* dad;
    LKHNode* specialDad;
    LKHNode* mark;

    Candidate* candidateSet;
};

struct Candidate {
    Cost alpha;
    LKHNode* adj;
    Candidate* suc;
};

struct Move {
    LKHNode *t1, *t2, *t3, *t4;

    Move() { }

    Move(LKHNode *a, LKHNode *b, LKHNode *c, LKHNode *d)
    : t1(a), t2(b), t3(c), t4(d) {

    }
};


size_t maxCandidates = 30;
size_t maxRuns = 20;
size_t maxTrials = 20;

bool restoring = false;
bool adjusting = false;

int orientation = 1;

Vertex firstId = 0;
Period initialPeriod = 0;
Real initialStepSize = 1.0;
Cost EPS = 1e-2;

LKHNode *nodesBuffer = nullptr;
LKHNode *firstNode = nullptr;       // "First" node in the graph
LKHNode *specialNode = nullptr;     // Special node in the 1Tree
// Candidate *originalCandidates = nullptr;
stack<Move> moves;

Norm treeNorm = 0;

CostMatrix *graph = nullptr;

BoolMatrix *fixedEdge;

Tour *betterTour, *bestTour;







inline void follow(LKHNode*, LKHNode*);
inline bool between(LKHNode*, LKHNode*, LKHNode*);
bool checkOrder();


inline void follow(LKHNode *fst, LKHNode *snd)
{
    snd->pre->suc = snd->suc;
    snd->suc->pre = snd->pre;
    fst->suc->pre = snd;
    snd->suc = fst->suc;
    fst->suc = snd;
    snd->pre = fst;
}


// Check if a --> b --> c
inline bool between(LKHNode *tx, LKHNode *ty, LKHNode *tz)
{
    Position x = tx->pos, y = ty->pos, z = tz->pos;
    if(orientation == false) {
        swap(x, z);
    }

    return (x <= z) ? (y >= x and y <= z) : (y >= x or y <= z);
}

bool checkOrder()
{
    auto current = firstNode;
    int cnt = dimGraph;
    do {
        if((current->suc->pos) != (current->pos+1)%dimGraph) {
            cerr << "error in " << current->pos << " -> " << current->suc->pos << endl;
            return false;
        }
        cnt--;
    }while((current = current->suc) != firstNode);

    if(cnt > 0) {
        cerr << "COUNTTTTT\n";
        abort();
    }

    return cnt == 0;
}


#endif