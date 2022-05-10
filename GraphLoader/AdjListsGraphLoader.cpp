//
// Created by Dell on 28. 10. 2021.
//

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>
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


    unsigned int numberOfVertices;
    /*Pokusi sa pomocou txt suboru vytvorit korektny kubicky graf */
    try {
        if (!f) {
            throw FileCannotBeOpenedException();
        }
        f >> numberOfVertices;
        if (numberOfVertices < 0){
            throw WrongNumberOfVerticesException();
        }

        //while graph can be loaded, load next graph - function loadGraph does both at once
        while(loadGraph(graphList, f, numberOfVertices, coloringAlgorithm));

    } catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }

    informationFromFile.erase();
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
