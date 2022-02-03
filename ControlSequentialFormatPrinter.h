//
// Created by Dell on 22. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CONTROLSEQUENTIALFORMATPRINTER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CONTROLSEQUENTIALFORMATPRINTER_H


#include "CubicGraph.h"
#include "Enums.h"
#include "GraphPrinter.h"

class ControlSequentialFormatPrinter : public GraphPrinter {
public:
    ControlSequentialFormatPrinter()=default;;

    bool print(CubicGraph& cubicGraph, const std::string& filename, append append) override;
    bool print(std::vector<CubicGraph>& graphList, const std::string& filename, append append) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CONTROLSEQUENTIALFORMATPRINTER_H
