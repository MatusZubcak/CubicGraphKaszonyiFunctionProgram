//
// Created by Dell on 3. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTER_H

#include "CubicGraph.h"
#include "Enums.h"

class GraphPrinter{
public:
    virtual bool printGraph(CubicGraph& cubicGraph, const std::string& filename, append append) =0;
    virtual bool printKaszonyiValue_forSingleEdge(CubicGraph& cubicGraph, const std::string& filename, Edge edge,
                                                  append append) =0;
    virtual bool printKaszonyiValue_forAllEdges(CubicGraph& cubicGraph, const std::string& filename, append append) =0;
    virtual ~GraphPrinter()= default;;

};

#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTER_H
