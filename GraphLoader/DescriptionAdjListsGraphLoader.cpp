//
// Created by Dell on 4. 2. 2022.
//

#include "DescriptionAdjListsGraphLoader.h"
#include <fstream>
#include <iostream>


std::string DescriptionAdjListsGraphLoader::loadAdditionalInformation(std::ifstream &f) {
    std::string informationString;
    std::string getline_str;

    while(f.peek() != '{'){
        std::getline(f, getline_str);
    }
    getline_str.erase();

    while(f.peek() == '{'){
        std::getline(f, getline_str);
        informationString += getline_str + '\n';
    }

    return informationString;
}

std::vector<CubicGraph>
DescriptionAdjListsGraphLoader::loadNewGraphs(const std::string &filename, std::string &informationFromFile,
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
        //Load information in brackets to informationFromFile string
        informationFromFile = loadAdditionalInformation(f);

        f >> numberOfVertices;
        if (numberOfVertices < 0){
            throw WrongNumberOfVerticesException();
        }

        int dump_int;
        //While graph can be loaded, load next graph - function loadGraph does both at once
        while(loadGraph(graphList, f, numberOfVertices, coloringAlgorithm)){
        }

    } catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }

    return graphList;
}

std::vector<CubicGraph> DescriptionAdjListsGraphLoader::loadNewGraphs(const std::string &filename,
                                                                      std::string &informationFromFile) {
    return loadNewGraphs(filename, informationFromFile, ANY);
}

std::vector<CubicGraph> DescriptionAdjListsGraphLoader::loadNewGraphs(const std::string &filename) {
    std::string dump_string;
    return loadNewGraphs(filename, dump_string,ANY);
}

std::vector<CubicGraph> DescriptionAdjListsGraphLoader::loadNewGraphs(const std::string &filename,
                                                                      coloringAlgorithm coloringAlgorithm) {
    std::string dump_string;
    return loadNewGraphs(filename, dump_string, coloringAlgorithm);
}
