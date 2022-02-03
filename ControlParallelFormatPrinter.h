//
// Created by Dell on 23. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CONTROLPARALLELFORMATPRINTER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CONTROLPARALLELFORMATPRINTER_H


#include "GraphPrinter.h"

class ControlParallelFormatPrinter : public GraphPrinter{
public:
    ControlParallelFormatPrinter()=default;;

    bool print(CubicGraph& cubicGraph, const std::string& filename, append append) override;
    bool print(std::vector<CubicGraph>& graphList, const std::string& filename, append append) override;

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CONTROLPARALLELFORMATPRINTER_H
