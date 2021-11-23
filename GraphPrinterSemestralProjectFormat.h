//
// Created by Dell on 3. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTERSEMESTRALPROJECTFORMAT_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTERSEMESTRALPROJECTFORMAT_H


#include <vector>
#include "GraphPrinter.h"

class GraphPrinterSemestralProjectFormat : GraphPrinter {
public:
        GraphPrinterSemestralProjectFormat()=default;;

        bool printGraph(CubicGraph& cubicGraph, const std::string& filename, append append) override;
        bool printKaszonyiValues(CubicGraph& cubicGraph, const std::string& filename, append append) override;
        bool printKaszonyiValues(std::queue<CubicGraph>& graphQueue, const std::string& filename, append append) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTERSEMESTRALPROJECTFORMAT_H
