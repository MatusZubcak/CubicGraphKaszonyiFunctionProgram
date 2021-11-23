//
// Created by Dell on 2. 11. 2021.
//

#include <fstream>
#include <iostream>
#include <vector>
#include "GraphPrinterZeroDepthFormat.h"

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

/*
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
*/

bool GraphPrinterZeroDepthFormat::printKaszonyiValues(CubicGraph &cubicGraph, const std::string &filename,
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

bool GraphPrinterZeroDepthFormat::printKaszonyiValues(std::queue<CubicGraph> &graphQueue, const std::string &filename,
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
        bool firstGraph = true;

        while(!graphQueue.empty()){
            CubicGraph cubicGraph = graphQueue.front();
            graphQueue.pop();

            if(firstGraph){
                f << cubicGraph.size() << std::endl;
                firstGraph = false;
            }


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
