//
// Created by Dell on 23. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PARALLELPATHPRINTER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PARALLELPATHPRINTER_H


#include "GraphPrinter.h"

class ParallelPathPrinter : public GraphPrinter{
public:
    ParallelPathPrinter()=default;;

    bool print(CubicGraph& cubicGraph, const std::string& filename, append append) override;
    bool print(std::vector<CubicGraph>& graphList, const std::string& filename, append append) override;
    bool print(CubicGraph &cubicGraph, const std::string &filename, const std::string &additionalInformation,
               append append) override;
    bool print(std::vector<CubicGraph> &graphList, const std::string &filename,
               const std::string &additionalInformation, append append) override;

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PARALLELPATHPRINTER_H
