//
// Created by Dell on 22. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTERSEQUENTIALFORMAT_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTERSEQUENTIALFORMAT_H


#include "CubicGraph.h"
#include "Enums.h"
#include "GraphPrinter.h"

class GraphPrinterSequentialFormat : GraphPrinter {
public:
    GraphPrinterSequentialFormat()=default;;

    bool printGraph(CubicGraph& cubicGraph, const std::string& filename, append append) override;
    bool printKaszonyiValues(CubicGraph& cubicGraph, const std::string& filename, append append) override;
    bool printKaszonyiValues(std::vector<CubicGraph>& graphList, const std::string& filename, append append) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTERSEQUENTIALFORMAT_H
