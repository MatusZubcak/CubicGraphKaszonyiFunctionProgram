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

        CubicGraph graph = graphQueue.front();
        graphQueue.pop();

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

    //TODO This was for time being removed, so the last graph in queue is the first graph with coloring
    /*
    while(!graphQueue.empty()){
        CubicGraph graph = graphQueue.front();
        graphQueue.pop();

        if(graph.getDepth() <= depth){
            finalGraphQueue.push(graph);
        }
    }
     */

    return finalGraphQueue;
}
