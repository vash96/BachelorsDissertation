#ifndef UTIL_TYPES
#define UTIL_TYPES

#include <vector>
#include <list>
#include <array>
#include <utility> // pair<>
#include <queue> // priority_queue<>
#include <stack>
using namespace std;

typedef int Vertex;
typedef int Position;
typedef double Cost;
typedef double Real;
typedef double Time;

typedef struct HeapElement HeapElement;

struct HeapElement {
    Position x, y;
    Cost fValue;

    HeapElement() { }
    HeapElement(Position xx, Position yy, Cost ff)
    : x(xx), y(yy), fValue(ff) { }

    bool operator<(const HeapElement & other) const {
        return fValue < other.fValue;
    }
};

typedef pair<Vertex, Vertex> Edge;
typedef pair<Vertex, Cost> WeightedDestination;
typedef pair<Vertex, int> EdgeLabeled;
typedef pair<Real, Real> Point;

typedef vector<Position> Permutation;
typedef vector<Vertex> Tour;
typedef vector<bool> BoolVec;
typedef vector<Edge> SpanningTree;
typedef vector<Edge> Matching;
typedef vector<vector<WeightedDestination>> WeightedGraph;
typedef vector<vector<EdgeLabeled>> GraphLabeled;
typedef vector<vector<Vertex>> Graph;
typedef vector<vector<Vertex>> Tree;
typedef vector<vector<Cost>> CostMatrix;
typedef vector<BoolVec> BoolMatrix;

typedef list<Vertex> TourList;

typedef array<int, 2> ReinsertionScheme;

typedef priority_queue<HeapElement> MaxHeap;

#endif