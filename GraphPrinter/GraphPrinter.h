//
// Created by Dell on 3. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTER_H

#include "../CubicGraph.h"
#include "../Enums.h"
#include <vector>

class GraphPrinter{
protected:
    std::vector<std::vector<unsigned int>> toAdjacencyList(CubicGraph& cubicGraph);
    bool printGraph(CubicGraph &cubicGraph, std::ofstream &f);
    bool printKaszonyiValues(CubicGraph &cubicGraph, std::ofstream &f, edgesFormat edgesFormat);
    bool printIdAndDepth(CubicGraph& cubicGraph, std::ofstream &f);

public:
    virtual bool print(CubicGraph& cubicGraph, const std::string& filename, append append) =0;
    virtual bool print(std::vector<CubicGraph>& graphList, const std::string& filename, append append) =0;
    virtual bool print(CubicGraph& cubicGraph, const std::string& filename, const std::string& additionalInformation,
                       append append) =0;
    virtual bool print(std::vector<CubicGraph>& graphList, const std::string& filename,
                       const std::string& additionalInformation, append append) =0;
    virtual ~GraphPrinter()= default;;

};

#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHPRINTER_H
