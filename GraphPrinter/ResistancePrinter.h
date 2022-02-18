//
// Created by Dell on 31. 1. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_RESISTANCEPRINTER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_RESISTANCEPRINTER_H

#include "GraphPrinter.h"

class ResistancePrinter : public GraphPrinter {
public:

    bool print(CubicGraph &cubicGraph, const std::string &filename, append append) override;
    bool print(std::vector<CubicGraph> &graphList, const std::string &filename, append append) override;
    bool print(CubicGraph &cubicGraph, const std::string &filename, const std::string &additionalInformation,
               append append) override;
    bool print(std::vector<CubicGraph> &graphList, const std::string &filename,
               const std::string &additionalInformation, append append) override;

private:
    bool printResistanceValues(CubicGraph& cubicGraph, std::ofstream& f);
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_RESISTANCEPRINTER_H
