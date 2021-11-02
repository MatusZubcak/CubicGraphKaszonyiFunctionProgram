//
// Created by Dell on 2. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTER_H


#include "CubicGraph.h"
#include "Enums.h"

class GraphPrinter {
private:
    std::vector<std::pair<unsigned int, bool>> getLinearGraphRepresentation(CubicGraph& cubicGraph);
public:
    GraphPrinter()=default;;
    bool printGraph_adjListsFormat(CubicGraph& cubicGraph, const std::string& filename, append append);

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTER_H
