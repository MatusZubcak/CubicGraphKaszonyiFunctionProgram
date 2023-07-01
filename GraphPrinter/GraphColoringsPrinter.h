//
// Created by matus on 30.6.2023.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHCOLORINGSPRINTER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHCOLORINGSPRINTER_H


#include "GraphPrinter.h"

class GraphColoringsPrinter: public GraphPrinter {
public:
    GraphColoringsPrinter()=default;;

    bool print(CubicGraph& cubicGraph, const std::string& filename, append append) override;
    bool print(std::vector<CubicGraph>& graphList, const std::string& filename, append append) override;
    bool print(CubicGraph &cubicGraph, const std::string &filename, const std::vector<std::string>& additionalInformation,
               append append) override;
    bool print(std::vector<CubicGraph> &graphList, const std::string &filename,
               const std::vector<std::string>& additionalInformation, append append) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHCOLORINGSPRINTER_H
