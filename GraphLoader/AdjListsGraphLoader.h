//
// Created by Dell on 28. 10. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_ADJLISTSGRAPHLOADER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_ADJLISTSGRAPHLOADER_H

#include <vector>
#include "GraphLoader.h"

class AdjListsGraphLoader : public GraphLoader {

public:
    AdjListsGraphLoader()= default;;
    std::vector<CubicGraph> loadNewGraphs(const std::string& filename, std::string& informationFromFile) override;
    std::vector<CubicGraph> loadNewGraphs(const std::string &filename, std::string& informationFromFile,
                                          coloringAlgorithm coloringAlgorithm) override;
    std::vector<CubicGraph> loadNewGraphs(const std::string &filename) override;
    std::vector<CubicGraph> loadNewGraphs(const std::string &filename, coloringAlgorithm coloringAlgorithm) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_ADJLISTSGRAPHLOADER_H
