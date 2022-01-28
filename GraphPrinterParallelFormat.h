//
// Created by Dell on 23. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTERPARALLELFORMAT_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTERPARALLELFORMAT_H


#include "GraphPrinter.h"

class GraphPrinterParallelFormat : GraphPrinter{
public:
    GraphPrinterParallelFormat()=default;;

    bool printGraph(CubicGraph& cubicGraph, const std::string& filename, append append) override;
    bool printKaszonyiValues(CubicGraph& cubicGraph, const std::string& filename, append append) override;
    bool printKaszonyiValues(std::vector<CubicGraph>& graphList, const std::string& filename, append append) override;

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTERPARALLELFORMAT_H
