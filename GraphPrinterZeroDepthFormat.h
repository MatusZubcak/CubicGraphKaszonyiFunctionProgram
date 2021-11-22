//
// Created by Dell on 2. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTERZERODEPTHFORMAT_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTERZERODEPTHFORMAT_H


#include <queue>
#include "CubicGraph.h"
#include "Enums.h"
#include "GraphPrinter.h"

class GraphPrinterZeroDepthFormat : GraphPrinter {
private:
    std::vector<std::pair<unsigned int, bool>> getLinearGraphRepresentation(CubicGraph& cubicGraph);
public:
    GraphPrinterZeroDepthFormat()=default;;

    bool printGraph(CubicGraph& cubicGraph, const std::string& filename, append append) override;
    bool printKaszonyiValue_forSingleEdge(CubicGraph& cubicGraph, const std::string& filename, Edge edge,
                                          append append) override;
    bool printKaszonyiValue_forAllEdges(CubicGraph& cubicGraph, const std::string& filename, append append) override;
    bool printGraphQueue(std::queue<CubicGraph>& graphQueue, const std::string& filename, append append);
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTERZERODEPTHFORMAT_H
