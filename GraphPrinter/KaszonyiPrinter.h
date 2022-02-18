//
// Created by Dell on 2. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_KASZONYIPRINTER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_KASZONYIPRINTER_H


#include "../CubicGraph.h"
#include "../Enums.h"
#include "GraphPrinter.h"

class KaszonyiPrinter : public GraphPrinter {
public:
    KaszonyiPrinter()=default;;

    bool print(CubicGraph& cubicGraph, const std::string& filename, append append) override;
    bool print(std::vector<CubicGraph>& graphList, const std::string& filename, append append) override;
    bool print(CubicGraph &cubicGraph, const std::string &filename, const std::string &additionalInformation,
               append append) override;
    bool print(std::vector<CubicGraph> &graphList, const std::string &filename,
               const std::string &additionalInformation, append append) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_KASZONYIPRINTER_H
