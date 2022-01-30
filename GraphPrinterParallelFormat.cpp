//
// Created by Dell on 23. 11. 2021.
//

#include <fstream>
#include <iostream>
#include <map>
#include "GraphPrinterParallelFormat.h"
#include "ParallelSuppressionNaive.h"
#include "ParallelSuppressionMemoized.h"


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

        //NAIVE SUPPRESSION
        //ParallelSuppressionNaive parallelSuppression = ParallelSuppressionNaive();

        //MEMOIZED SUPPRESSION
        ParallelSuppressionMemoized parallelSuppression = ParallelSuppressionMemoized();

        std::vector<CubicGraph> suppressionSequence = parallelSuppression.findSuppressionSequence(cubicGraph);
        /*bool firstGraph = true;
        unsigned int maxDepth = 0;

        //TODO this is new
        std::map<unsigned int, CubicGraph> graphDict;
        CubicGraph lastGraph = graphList.back();
        maxDepth = lastGraph.getDepth();
        for(const auto& graph : graphList) {
            graphDict.insert({graph.getId(), graph});
        }

        CubicGraph parentGraph = lastGraph;
        std::vector<CubicGraph> listOfSuppressedGraphs;
        while(parentGraph.getId() != 0) {
            listOfSuppressedGraphs.push_back(parentGraph);
            unsigned int parent_id = parentGraph.getParentId();
            parentGraph = graphDict[parent_id];
        }
        listOfSuppressedGraphs.push_back(parentGraph);*/


        bool firstGraph = true;
        // TODO NEW PART - ONLY SUCCESSFUL PATH PRINTED
        for(auto graph : suppressionSequence) {
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
                if(e.isOriginal())
                    f << e.toString() << ": " << graph.getKaszonyiValue(e) << " is original" << std::endl;
                else
                    f << e.toString() << ": " << graph.getKaszonyiValue(e) << std::endl;
            }

                f << std::endl;
            }
            f << "Depth: " << suppressionSequence.back().getDepth() << std::endl;
            f.close();
    }catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }
    return true;
}



    //TODO OLD PART - WITH QUEUE - ALL GRAPHS PRINTED - look for commented parts here (remove)
    /*
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
}
     */

bool GraphPrinterParallelFormat::printKaszonyiValues(std::vector<CubicGraph> &graphList, const std::string &filename,
                                                       append append) {
    return false;
}
