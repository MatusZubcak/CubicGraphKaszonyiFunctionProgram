//
// Created by Dell on 22. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALPATHPRINTER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALPATHPRINTER_H


#include "../CubicGraph.h"
#include "../Enums.h"
#include "GraphPrinter.h"

class SequentialPathPrinter : public GraphPrinter {
public:
    SequentialPathPrinter()=default;;

    bool print(CubicGraph& cubicGraph, const std::string& filename, append append) override;
    bool print(std::vector<CubicGraph>& graphList, const std::string& filename, append append) override;
    bool print(CubicGraph &cubicGraph, const std::string &filename, const std::string &additionalInformation,
               append append) override;
    bool print(std::vector<CubicGraph> &graphList, const std::string &filename,
               const std::string &additionalInformation, append append) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALPATHPRINTER_H
