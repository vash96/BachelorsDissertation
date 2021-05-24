#ifndef UTIL_READINPUT
#define UTIL_READINPUT

#include "types.cpp"
#include "constants.cpp"
#include <string>
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

CostMatrix* readInput();
inline Real euc_2d(Point, Point);

CostMatrix* readInput()
{
    string token;
    string name;
    string type;
    string dist;

    cin >> token >> token >> name; // NAME
    cin >> token >> token; getline(cin, token); // COMMENT
    cin >> token >> token >> type; // TYPE
    cin >> token >> token >> dimGraph; // DIMENSION
    cin >> token >> token >> dist; // EDGE_WEIGHT_TYPE
    cin >> token; // NODE_COORD_SECTION

    auto graph = new CostMatrix(dimGraph, vector<Cost>(dimGraph, 0.0));

    if(type.compare("TSP")==0 and dist.compare("EUC_2D")==0) {

        // Collecting points
        vector<Point> points(dimGraph);
        int idx; Real x, y;
        for(size_t i=0, idx; i<dimGraph; ++i) {
            cin >> idx >> x >> y;
            points[i] = {x, y};
        }

        for(Vertex u=0; (size_t)u<dimGraph; ++u) {
            for(Vertex v=u+1; (size_t)v<dimGraph; ++v) {
                (*graph)[u][v] = (*graph)[v][u] = euc_2d(points[u], points[v]);
            }
        }
    }else if(type.compare("CUSTOM")==0 and dist.compare("CUSTOM")==0) {

        // Here we have the complete cost matrix, just read it
        for(auto & row : (*graph)) {
            for(auto & val : row) {
                cin >> val;
            }
        }
    
    }else {
        cerr << "Lettura non supportata!\n";
        abort();
    }

    return graph;
}

inline Real euc_2d(Point a, Point b)
{
    return sqrt((a.first-b.first)*(a.first-b.first) + (a.second-b.second)*(a.second-b.second));
}

#endif