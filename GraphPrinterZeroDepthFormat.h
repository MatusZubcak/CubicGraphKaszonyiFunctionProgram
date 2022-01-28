//
// Created by Dell on 2. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTERZERODEPTHFORMAT_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTERZERODEPTHFORMAT_H


#include "CubicGraph.h"
#include "Enums.h"
#include "GraphPrinter.h"

class GraphPrinterZeroDepthFormat : GraphPrinter {
public:
    GraphPrinterZeroDepthFormat()=default;;

    bool printGraph(CubicGraph& cubicGraph, const std::string& filename, append append) override;
    bool printKaszonyiValues(CubicGraph& cubicGraph, const std::string& filename, append append) override;
    bool printKaszonyiValues(std::vector<CubicGraph>& graphList, const std::string& filename, append append) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTERZERODEPTHFORMAT_H
