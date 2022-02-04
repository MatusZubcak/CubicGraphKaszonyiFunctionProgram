//
// Created by Dell on 28. 10. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADERSIMPLEADJLISTSFORMAT_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADERSIMPLEADJLISTSFORMAT_H

#include <vector>
#include "GraphLoader.h"

class GraphLoaderSimpleAdjListsFormat : public GraphLoader {

public:
    GraphLoaderSimpleAdjListsFormat()= default;;
    std::vector<CubicGraph> loadNewGraphs(const std::string& filename, std::string& InformationFromFile) override;
    std::vector<CubicGraph> loadNewGraphs(const std::string &filename, std::string& InformationFromFile,
                                          coloringAlgorithm coloringAlgorithm) override;
    std::vector<CubicGraph> loadNewGraphs(const std::string &filename) override;
    std::vector<CubicGraph> loadNewGraphs(const std::string &filename, coloringAlgorithm coloringAlgorithm) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADERSIMPLEADJLISTSFORMAT_H
