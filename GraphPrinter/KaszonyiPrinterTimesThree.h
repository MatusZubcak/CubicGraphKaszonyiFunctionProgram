//
// Created by Dell on 2. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_KASZONYIPRINTERTIMESTHREE_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_KASZONYIPRINTERTIMESTHREE_H


#include "../CubicGraph.h"
#include "../Enums.h"
#include "GraphPrinter.h"

class KaszonyiPrinterTimesThree : public GraphPrinter {
public:
    KaszonyiPrinterTimesThree()=default;;

    bool print(CubicGraph& cubicGraph, const std::string& filename, append append) override;
    bool print(std::vector<CubicGraph>& graphList, const std::string& filename, append append) override;
    bool print(CubicGraph &cubicGraph, const std::string &filename, const std::string &additionalInformation,
               append append) override;
    bool print(std::vector<CubicGraph> &graphList, const std::string &filename,
               const std::string &additionalInformation, append append) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_KASZONYIPRINTERTIMESTHREE_H
