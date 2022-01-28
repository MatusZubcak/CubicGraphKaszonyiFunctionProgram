//
// Created by Dell on 3. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTER_H

#include "CubicGraph.h"
#include "Enums.h"
#include <vector>

class GraphPrinter{
protected:
    std::vector<std::pair<unsigned int, bool>> getLinearGraphRepresentation(CubicGraph& cubicGraph);

public:
    virtual bool printGraph(CubicGraph& cubicGraph, const std::string& filename, append append) =0;
    virtual bool printKaszonyiValues(CubicGraph& cubicGraph, const std::string& filename, append append) =0;
    virtual bool printKaszonyiValues(std::vector<CubicGraph>& graphList, const std::string& filename, append append) =0;
    virtual ~GraphPrinter()= default;;

};

#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTER_H
