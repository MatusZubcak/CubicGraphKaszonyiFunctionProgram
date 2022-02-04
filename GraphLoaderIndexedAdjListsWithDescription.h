//
// Created by Dell on 4. 2. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADERINDEXEDADJLISTSWITHDESCRIPTION_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADERINDEXEDADJLISTSWITHDESCRIPTION_H

#include <vector>
#include "GraphLoader.h"

class GraphLoaderIndexedAdjListsWithDescription : public GraphLoader {
public:
    std::vector<CubicGraph> loadNewGraphs(const std::string& filename, std::string& InformationFromFile) override;
    std::vector<CubicGraph> loadNewGraphs(const std::string &filename, std::string& InformationFromFile,
                                          coloringAlgorithm coloringAlgorithm) override;
    std::vector<CubicGraph> loadNewGraphs(const std::string &filename) override;
    std::vector<CubicGraph> loadNewGraphs(const std::string &filename, coloringAlgorithm coloringAlgorithm) override;

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADERINDEXEDADJLISTSWITHDESCRIPTION_H
