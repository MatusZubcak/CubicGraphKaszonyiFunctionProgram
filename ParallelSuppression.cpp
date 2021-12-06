//
// Created by Dell on 23. 11. 2021.
//

#include <iostream>
#include "ParallelSuppression.h"

std::queue<CubicGraph> ParallelSuppression::findDepth(const CubicGraph& cubicGraph) {
    unsigned long long unique_id = cubicGraph.getId() +1;

    std::queue<CubicGraph> graphQueue;
    std::queue<CubicGraph> finalGraphQueue;
    graphQueue.push(cubicGraph);
    unsigned int depth = 0;
    bool coloringFound = false;

    while(!graphQueue.empty() && !coloringFound){
        //TODO look for commented parts here (remove)

        /*
         if(unique_id % 1000 == 0) {
            std::cout << unique_id << std::endl;
        }
        */

        CubicGraph graph = graphQueue.front();
        graphQueue.pop();

        /*
        if(unique_id >= 3985000){
            std::cout << "Queue_size: " << graphQueue.size() << std::endl;
            std::cout << "ID: " <<graph.getId() << " PARENT: " << graph.getParentId() << std::endl;
            std::cout << "Depth: " << graph.getDepth() << std::endl;
            std::cout << graph.getVertices().size() << std::endl;
            for(auto e : graph.getEdges()){
                std::cout << e.toString() << " " << e.isOriginal() << std::endl;
            }
            std::cout << std::endl;
        }*/

        for(auto e : graph.getEdges()) {
            if(e.isOriginal()) {
                if(!e.isLoop()) {
                    if(graph.getKaszonyiValue(e) == 0) {
                        graphQueue.push(graph.suppressEdge(unique_id, e));
                        unique_id++;
                    }else {
                        coloringFound = true;
                        depth = graph.getDepth();
                    }
                }
            }
        }
        finalGraphQueue.push(graph);
    }

    while(!graphQueue.empty()){
        CubicGraph graph = graphQueue.front();
        graphQueue.pop();

        if(graph.getDepth() <= depth){
            /*
            for(auto e : graph.getEdges()){
                graph.getKaszonyiValue(e);
            }
            */
            finalGraphQueue.push(graph);
        }
    }

    //TODO remove this eventually
    std::cout << "RETURNING..." << std::endl;

    return finalGraphQueue;
}
