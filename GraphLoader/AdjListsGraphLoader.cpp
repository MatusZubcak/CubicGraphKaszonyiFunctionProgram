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

std::vector<CubicGraph> AdjListsGraphLoader::loadNewGraphs(const std::string& filename,
                                                           std::string& informationFromFile,
                                                           coloringAlgorithm coloringAlgorithm) {
    std::vector<CubicGraph> graphList = {};
    std::ifstream f;
    f.open(filename);
    std::string buffer, word;
    std::vector<std::string> stringList;


    unsigned int numberOfVertices;
    /*Pokusi sa pomocou txt suboru vytvorit korektny kubicky graf */

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

        //while graph can be loaded, load next graph - function loadGraph does both at once
        while(loadGraph(graphList, f, numberOfVertices, coloringAlgorithm));

    /*} catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }*/

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
