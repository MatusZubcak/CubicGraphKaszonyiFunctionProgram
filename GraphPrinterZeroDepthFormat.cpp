//
// Created by Dell on 2. 11. 2021.
//

#include <fstream>
#include <iostream>
#include <vector>
#include "GraphPrinterZeroDepthFormat.h"

std::vector<std::pair<unsigned int, bool>>
GraphPrinterZeroDepthFormat::getLinearGraphRepresentation(CubicGraph &cubicGraph){

    std::vector<std::pair<unsigned int, bool>>linearGraphRepresentation
            (3*cubicGraph.size(), std::pair<int,bool>(0, true));

    for(auto e : cubicGraph.getEdges()){
        unsigned int v1 = e.getIncidentvertices().first;
        unsigned int v2 = e.getIncidentvertices().second;
        unsigned int v1VectorIndex = 3*v1;
        unsigned int v2VectorIndex = 3*v2;

        for(int repeats = 0; repeats < e.getMultiplicity(); repeats++) {
            for (unsigned int i = v1VectorIndex; i < v1VectorIndex + 3; i++) {
                if (linearGraphRepresentation[i].second) {
                    linearGraphRepresentation[i].first = v2;
                    linearGraphRepresentation[i].second = false;
                    break;
                }
            }
            for (unsigned int i = v2VectorIndex; i < v2VectorIndex + 3; i++) {
                if (linearGraphRepresentation[i].second) {
                    linearGraphRepresentation[i].first = v1;
                    linearGraphRepresentation[i].second = false;
                    break;
                }
            }
        }
    }
    return linearGraphRepresentation;
}

bool GraphPrinterZeroDepthFormat::printGraph(CubicGraph &cubicGraph, const std::string& filename, append append) {
    std::ofstream f;
    if(append == APPEND)
        f.open(filename, std::ios::app);
    else
        f.open(filename);

    try{
        if (!f) {
            throw FileCannotBeOpenedException();
        }
        std::vector<std::pair<unsigned int, bool>> linearGraphRepresentation = getLinearGraphRepresentation(cubicGraph);
        std::set<unsigned int> vertices = cubicGraph.getVertices();

        auto it = vertices.begin();
        for(int i = 0; i < cubicGraph.size(); i++){
            f << *it << ": "
              << linearGraphRepresentation[3*i].first << " "
              << linearGraphRepresentation[3*i+1].first << " "
              << linearGraphRepresentation[3*i+2].first
              << std::endl;
            it++;
        }

        f << "Number of isolated circles: " << cubicGraph.getNumberOfIsolatedCircles() << std::endl;
        f.close();
    }catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }
    return true;
}

bool GraphPrinterZeroDepthFormat::printKaszonyiValue_forSingleEdge(CubicGraph &cubicGraph, const std::string &filename,
                                                                   Edge edge,
                                                                   append append) {
    std::ofstream f;
    if(append == APPEND)
        f.open(filename, std::ios::app);
    else
        f.open(filename);

    try{
        if (!f) {
            throw FileCannotBeOpenedException();
        }
        f << edge.toString() << ": " << cubicGraph.getKaszonyiValue(edge) << std::endl;
        f.close();
    }catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }
    return true;
}

bool GraphPrinterZeroDepthFormat::printKaszonyiValue_forAllEdges(CubicGraph &cubicGraph, const std::string &filename,
                                                                 append append) {
    std::ofstream f;
    if(append == APPEND)
        f.open(filename, std::ios::app);
    else
        f.open(filename);

    try{
        if (!f) {
            throw FileCannotBeOpenedException();
        }
        for(auto e : cubicGraph.getEdges()) {
            f << e.toString() << ": " << cubicGraph.getKaszonyiValue(e) << std::endl;
        }
        f.close();
    }catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }
    return true;
}

bool GraphPrinterZeroDepthFormat::printGraphQueue(std::queue<CubicGraph> &graphQueue, const std::string &filename,
                                                  append append) {
    std::ofstream f;
    if(append == APPEND)
        f.open(filename, std::ios::app);
    else
        f.open(filename);

    try{
        if (!f) {
            throw FileCannotBeOpenedException();
        }
        CubicGraph cubicGraph = graphQueue.front();
        f << cubicGraph.size() << std::endl;
        while(!graphQueue.empty()){
            std::vector<std::pair<unsigned int, bool>> linearGraphRepresentation =
                    getLinearGraphRepresentation(cubicGraph);
            std::set<unsigned int> vertices = cubicGraph.getVertices();

            auto it = vertices.begin();
            for(int i = 0; i < cubicGraph.size(); i++){
                f << *it << ": "
                  << linearGraphRepresentation[3*i].first << " "
                  << linearGraphRepresentation[3*i+1].first << " "
                  << linearGraphRepresentation[3*i+2].first
                  << std::endl;
                it++;
            }

            f << "Number of isolated circles: " << cubicGraph.getNumberOfIsolatedCircles() << std::endl;

            for(auto e : cubicGraph.getEdges()) {
                f << e.toString() << ": " << cubicGraph.getKaszonyiValue(e) << std::endl;
            }

            graphQueue.pop();
            if(!graphQueue.empty()){
                f << std::endl;
            }
        }
        f.close();
    }catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }
    return true;

}
