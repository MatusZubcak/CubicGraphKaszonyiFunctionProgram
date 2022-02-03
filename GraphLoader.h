//
// Created by Dell on 28. 10. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADER_H

#include "CubicGraph.h"
#include "Enums.h"

class GraphLoader{
public:
    virtual std::vector<CubicGraph> loadNewGraphs(const std::string& filename) = 0;
    virtual std::vector<CubicGraph> loadNewGraphs(const std::string& filename, coloringAlgorithm coloringAlgorithm) = 0;
};

#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADER_H
