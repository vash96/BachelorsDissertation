#ifndef ODD_DEGREE_VERTICES
#define ODD_DEGREE_VERTICES

vector<Vertex>* oddDegreeVertices(Graph*);

vector<Vertex>* oddDegreeVertices(Graph *graph)
{
    size_t dimGraph = graph->size();
    auto oddVertices = new vector<Vertex>;
    oddVertices->reserve(dimGraph);

    for(Vertex u=0; (size_t)u<dimGraph; ++u) {
        if((*graph)[u].size() & 1) {
            oddVertices->push_back(u);
        }
    }

    return oddVertices;
}

#endif