//
// Created by Dell on 28. 10. 2021.
//

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include "AdjListsGraphLoader.h"
#include "../Enums.h"
#include "../ColoringFinder/SATColoringFinder.h"
#include "../ColoringFinder/FactorColoringFinder.h"

// loads graphs from txt file in format written in program instructions
std::vector<CubicGraph> AdjListsGraphLoader::loadNewGraphs(const std::string& filename,
                                                           std::string& informationFromFile,
                                                           coloringAlgorithm coloringAlgorithm) {
    std::vector<CubicGraph> graphList = {};
    std::ifstream f;
    f.open(filename);
    std::string buffer, word;
    std::vector<std::string> stringList;


    unsigned int numberOfVertices;
    // tries generating correct cubic graph from text file

        if (!f.good()) {
            throw FileCannotBeOpenedException();
        }

        informationFromFile = loadAdditionalInformation(f);
        if(informationFromFile.empty()){
            f.close();
            f.open(filename);
            if (!f.good()) {
                throw FileCannotBeOpenedException();
            }
        }


        while(stringList.empty() && std::getline(f, buffer)) {
            std::stringstream stringStream(buffer);

            while (stringStream >> word) {
                stringList.push_back(word);
                if (stringList.size() > 1) {
                    throw WrongNumberOfVerticesException();
                } else if (stringList.size() == 1) {
                    numberOfVertices = std::stoul(stringList.front());
                }
            }
        }

        //while graph can be loaded, load next graph using function from GraphLoader
        while(loadGraph(graphList, f, numberOfVertices, coloringAlgorithm));

    f.close();
    return graphList;
}

std::vector<CubicGraph> AdjListsGraphLoader::loadNewGraphs(const std::string &filename,
                                                           std::string& informationFromFile) {
    return loadNewGraphs(filename, informationFromFile, ANY);
}

std::vector<CubicGraph> AdjListsGraphLoader::loadNewGraphs(const std::string &filename,
                                                           coloringAlgorithm coloringAlgorithm) {
    std::string dump_string;
    return loadNewGraphs(filename, dump_string, coloringAlgorithm);
}

std::vector<CubicGraph> AdjListsGraphLoader::loadNewGraphs(const std::string &filename) {
    std::string dump_string;
    return loadNewGraphs(filename, dump_string, ANY);
}
