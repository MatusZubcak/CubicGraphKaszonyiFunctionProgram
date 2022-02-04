//
// Created by Dell on 28. 10. 2021.
//

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include "GraphLoaderSimpleAdjListsFormat.h"
#include "Enums.h"
#include "ColoringFinderSAT.h"
#include "ColoringFinderFactor.h"

std::vector<CubicGraph> GraphLoaderSimpleAdjListsFormat::loadNewGraphs(const std::string& filename,
                                                                       std::string& InformationFromFile,
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

    InformationFromFile.erase();
    return graphList;
}

std::vector<CubicGraph> GraphLoaderSimpleAdjListsFormat::loadNewGraphs(const std::string &filename,
                                                                       std::string& InformationFromFile) {
    return loadNewGraphs(filename, InformationFromFile, ANY);
}

std::vector<CubicGraph> GraphLoaderSimpleAdjListsFormat::loadNewGraphs(const std::string &filename,
                                                                       coloringAlgorithm coloringAlgorithm) {
    std::string redundant_string;
    return loadNewGraphs(filename, redundant_string, coloringAlgorithm);
}

std::vector<CubicGraph> GraphLoaderSimpleAdjListsFormat::loadNewGraphs(const std::string &filename) {
    std::string redundant_string;
    return loadNewGraphs(filename, redundant_string, ANY);
}
