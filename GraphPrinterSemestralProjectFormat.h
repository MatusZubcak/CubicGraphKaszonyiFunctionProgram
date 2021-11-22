//
// Created by Dell on 3. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTERSEMESTRALPROJECTFORMAT_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTERSEMESTRALPROJECTFORMAT_H


#include <vector>
#include "GraphPrinter.h"

class GraphPrinterSemestralProjectFormat : GraphPrinter {
private:
        std::vector<std::pair<unsigned int, bool>> getLinearGraphRepresentation(CubicGraph& cubicGraph);

public:
        GraphPrinterSemestralProjectFormat()=default;;

        bool printGraph(CubicGraph& cubicGraph, const std::string& filename, append append) override;
        bool printKaszonyiValue_forSingleEdge(CubicGraph& cubicGraph, const std::string& filename, Edge edge,
                                              append append) override;
        bool printKaszonyiValue_forAllEdges(CubicGraph& cubicGraph, const std::string& filename, append append) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTERSEMESTRALPROJECTFORMAT_H
