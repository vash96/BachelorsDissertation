#ifndef GENERATE_CUSTOM_INPUT
#define GENERATE_CUSTOM_INPUT

#include "constants.cpp"
#include "types.cpp"
#include <string>
#include <fstream>

using namespace std;

void generateCustomInput(string&, CostMatrix*);

void generateCustomInput(string & filename, CostMatrix *graph)
{
    ofstream inputFile(filename);
    size_t dim = graph->size();

    inputFile << "NAME : custom" << dim << endl;
    inputFile << "COMMENT : nothing to say" << endl;
    inputFile << "TYPE : CUSTOM" << endl;
    inputFile << "DIMENSION : " << dim << endl;
    inputFile << "EDGE_WEIGHT_TYPE : CUSTOM" << endl;
    inputFile << "NODE_COORD_SECTION" << endl;
    
    for(auto & row : (*graph)) {
        for(auto val : row) {
            inputFile << val << " ";
        }
        inputFile << endl;
    }

    inputFile.close();
}

#endif