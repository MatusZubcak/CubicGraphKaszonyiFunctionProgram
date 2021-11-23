//
// Created by Dell on 23. 11. 2021.
//

#include <fstream>
#include <iostream>
#include "GraphPrinterParallelFormat.h"
#include "ParallelSuppression.h"


bool GraphPrinterParallelFormat::printGraph(CubicGraph &cubicGraph, const std::string& filename, append append) {
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


bool GraphPrinterParallelFormat::printKaszonyiValues(CubicGraph &cubicGraph, const std::string &filename,
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

        ParallelSuppression parallelSuppression = ParallelSuppression();
        std::queue<CubicGraph> graphQueue = parallelSuppression.findDepth(cubicGraph);
        bool firstGraph = true;
        while(!graphQueue.empty()){
            CubicGraph graph = graphQueue.front();
            graphQueue.pop();

            if(firstGraph){
                f << graph.size() << std::endl;
                firstGraph = false;
            }

            f << "Graph id: " << graph.getId() << std::endl;
            f << "Parent id: " << graph.getParentId() << std::endl;
            f << "Depth: " << graph.getDepth() << std::endl;

            std::vector<std::pair<unsigned int, bool>> linearGraphRepresentation =
                    getLinearGraphRepresentation(graph);
            std::set<unsigned int> vertices = graph.getVertices();

            auto it = vertices.begin();
            for(int i = 0; i < graph.size(); i++){
                f << *it << ": "
                  << linearGraphRepresentation[3*i].first << " "
                  << linearGraphRepresentation[3*i+1].first << " "
                  << linearGraphRepresentation[3*i+2].first
                  << std::endl;
                it++;
            }

            f << "Number of isolated circles: " << graph.getNumberOfIsolatedCircles() << std::endl;


            for(auto e : graph.getEdges()) {
                if(graph.getKaszonyiValue(e) != 0)
                    f << "****************" << std::endl
                      << e.toString() << ": " << graph.getKaszonyiValue(e) << std::endl
                      << "****************" << std::endl;
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

bool GraphPrinterParallelFormat::printKaszonyiValues(std::queue<CubicGraph> &graphQueue, const std::string &filename,
                                                       append append) {
    return false;
}

