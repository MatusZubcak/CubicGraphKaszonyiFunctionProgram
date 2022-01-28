//
// Created by Dell on 23. 11. 2021.
//

#include "SequentialSuppression.h"
#include <queue>
#include <iostream>

std::vector<CubicGraph> SequentialSuppression::findDepth(const CubicGraph& cubicGraph) {
    unsigned int unique_id = cubicGraph.getId() +1;

    std::queue<CubicGraph> graphQueue;
    std::vector<CubicGraph> graphList;
    graphQueue.push(cubicGraph);
    unsigned int depth = 0;
    bool coloringFound = false;

    while(!graphQueue.empty() && !coloringFound){
        CubicGraph graph = graphQueue.front();
        graphQueue.pop();
        for(auto e : graph.getEdges()) {
            if(!e.isLoop()) {
                CubicGraph suppressedGraph = graph.suppressEdge(unique_id, e);
                if (!suppressedGraph.isColorable()) {
                    graphQueue.push(suppressedGraph);
                    unique_id++;
                } else {
                    coloringFound = true;
                    depth = graph.getDepth();
                }
            }
        }
        graphList.push_back(graph);
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

    return graphList;
}
