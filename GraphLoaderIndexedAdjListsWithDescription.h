//
// Created by Dell on 4. 2. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADERINDEXEDADJLISTSWITHDESCRIPTION_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADERINDEXEDADJLISTSWITHDESCRIPTION_H

#include <vector>
#include "GraphLoader.h"

class GraphLoaderIndexedAdjListsWithDescription : public GraphLoader {
private:
    std::string loadAdditionalInformation(std::ifstream &f);
public:
    std::vector<CubicGraph> loadNewGraphs(const std::string& filename, std::string& informationFromFile) override;
    std::vector<CubicGraph> loadNewGraphs(const std::string &filename, std::string& informationFromFile,
                                          coloringAlgorithm coloringAlgorithm) override;
    std::vector<CubicGraph> loadNewGraphs(const std::string &filename) override;
    std::vector<CubicGraph> loadNewGraphs(const std::string &filename, coloringAlgorithm coloringAlgorithm) override;

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADERINDEXEDADJLISTSWITHDESCRIPTION_H
