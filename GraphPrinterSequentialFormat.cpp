//
// Created by Dell on 22. 11. 2021.
//

#include <fstream>
#include <iostream>
#include <map>
#include "GraphPrinterSequentialFormat.h"
#include "SequentialSuppression.h"

bool GraphPrinterSequentialFormat::printGraph(CubicGraph &cubicGraph, const std::string& filename, append append) {
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


bool GraphPrinterSequentialFormat::printKaszonyiValues(CubicGraph &cubicGraph, const std::string &filename,
                                                      append append) {
    std::ofstream f;
    if(append == APPEND)
        f.open(filename, std::ios::app);
    else
        f.open(filename);

    //TODO NEW FORMAT - WRITES ONLY SUCCESSFUL PATH
    try{
        if (!f) {
            throw FileCannotBeOpenedException();
        }

        SequentialSuppression sequentialSuppression = SequentialSuppression();
        std::queue<CubicGraph> graphQueue = sequentialSuppression.findDepth(cubicGraph);
        bool firstGraph = true;
        unsigned int maxDepth = 0;

        std::map<unsigned int, CubicGraph> graphDict;
        CubicGraph lastGraph = graphQueue.back();
        maxDepth = lastGraph.getDepth();
        while(!graphQueue.empty()) {
            CubicGraph cg = graphQueue.front();
            graphDict.insert({cg.getId(), cg});
            graphQueue.pop();
        }

        CubicGraph parentGraph = lastGraph;
        std::vector<CubicGraph> listOfSuppressedGraphs;
        while(parentGraph.getId() != 0) {
            listOfSuppressedGraphs.push_back(parentGraph);
            unsigned int parent_id = parentGraph.getParentId();
            parentGraph = graphDict[parent_id];
        }
        listOfSuppressedGraphs.push_back(parentGraph);


        while(!listOfSuppressedGraphs.empty()) {
            CubicGraph graph = listOfSuppressedGraphs.back();
            listOfSuppressedGraphs.pop_back();
            if (firstGraph) {
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
            for (int i = 0; i < graph.size(); i++) {
                f << *it << ": "
                  << linearGraphRepresentation[3 * i].first << " "
                  << linearGraphRepresentation[3 * i + 1].first << " "
                  << linearGraphRepresentation[3 * i + 2].first
                  << std::endl;
                it++;
            }

            f << "Number of isolated circles: " << graph.getNumberOfIsolatedCircles() << std::endl;

            for (auto e : graph.getEdges()) {
                //if(graph.getKaszonyiValue(e) != 0)
                //TODO fix output format
                f << e.toString() << ": " << graph.getKaszonyiValue(e) << std::endl;
            }

            if (!graphQueue.empty()) {
                f << std::endl;
            }
        }
        f << "Depth: " << maxDepth << std::endl;
        f.close();
    }catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }
    return true;
}


    /* TODO ORIGINAL FORMAT - PRINTS ALL GRAPHS
    try{
        if (!f) {
            throw FileCannotBeOpenedException();
        }

        SequentialSuppression sequentialSuppression = SequentialSuppression();
        std::queue<CubicGraph> graphQueue = sequentialSuppression.findDepth(cubicGraph);
        bool firstGraph = true;
        unsigned int maxDepth = 0;
        while(!graphQueue.empty()){
            CubicGraph graph = graphQueue.front();
            graphQueue.pop();
            maxDepth = std::max(maxDepth, graph.getDepth());

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
                //if(graph.getKaszonyiValue(e) != 0)
                //TODO fix output format
                    f << e.toString() << ": " << graph.getKaszonyiValue(e) << std::endl;
            }

            if(!graphQueue.empty()){
                f << std::endl;
            }
        }
        f << "Depth: " << maxDepth << std::endl;
        f.close();
    }catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }
    return true;
}*/

bool GraphPrinterSequentialFormat::printKaszonyiValues(std::queue<CubicGraph> &graphQueue, const std::string &filename,
                                                       append append) {
    return false;
}

