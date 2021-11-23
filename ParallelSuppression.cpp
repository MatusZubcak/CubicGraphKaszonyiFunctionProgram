//
// Created by Dell on 23. 11. 2021.
//

#include "ParallelSuppression.h"

std::queue<CubicGraph> ParallelSuppression::findDepth(const CubicGraph& cubicGraph) {
    unsigned int unique_id = cubicGraph.getId() +1;

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
                if (!e.isLoop() && graph.getKaszonyiValue(e) == 0) {
                    graphQueue.push(graph.suppressEdge(unique_id, e));
                    unique_id++;
                } else {
                    coloringFound = true;
                    depth = graph.getDepth();
                }
            }
        }
        finalGraphQueue.push(graph);
    }

    while(!graphQueue.empty()){
        CubicGraph graph = graphQueue.front();
        graphQueue.pop();
        if(graph.getDepth() <= depth){
            for(auto e : graph.getEdges()){
                graph.getKaszonyiValue(e);
            }
            finalGraphQueue.push(graph);
        }
    }

    return finalGraphQueue;
}
