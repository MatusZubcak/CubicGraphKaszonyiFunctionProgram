//
// Created by Dell on 31. 1. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_RESISTANCEVALUESPRINTER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_RESISTANCEVALUESPRINTER_H

#include "GraphPrinter.h"

class ResistanceValuesPrinter : public GraphPrinter {
public:

    bool print(CubicGraph &cubicGraph, const std::string &filename, append append) override;
    bool print(std::vector<CubicGraph> &graphList, const std::string &filename, append append) override;

private:
    bool printResistanceValues(CubicGraph& cubicGraph, std::ofstream& f);
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_RESISTANCEVALUESPRINTER_H
