//
// Created by Dell on 4. 2. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_DESCRIPTIONADJLISTSGRAPHLOADER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_DESCRIPTIONADJLISTSGRAPHLOADER_H

#include <vector>
#include "GraphLoader.h"

class DescriptionAdjListsGraphLoader : public GraphLoader {
private:
    std::string loadAdditionalInformation(std::ifstream &f);
public:
    std::vector<CubicGraph> loadNewGraphs(const std::string& filename, std::string& informationFromFile) override;
    std::vector<CubicGraph> loadNewGraphs(const std::string &filename, std::string& informationFromFile,
                                          coloringAlgorithm coloringAlgorithm) override;
    std::vector<CubicGraph> loadNewGraphs(const std::string &filename) override;
    std::vector<CubicGraph> loadNewGraphs(const std::string &filename, coloringAlgorithm coloringAlgorithm) override;

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_DESCRIPTIONADJLISTSGRAPHLOADER_H
