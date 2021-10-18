//
// Created by Dell on 18. 10. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CUBICGRAPH_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CUBICGRAPH_H


#include <set>
#include "Edge.h"

class CubicGraph {
private:
    std::set<unsigned int> vertices;
    std::set<Edge> edges;
    unsigned int depth;

public:
    CubicGraph(std::set<unsigned int>& vertices, std::set<Edge>& edges);

    std::set<Edge> getEdges();

    std::set<unsigned int> getVertices();

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CUBICGRAPH_H
