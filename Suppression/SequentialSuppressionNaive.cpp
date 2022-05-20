//
// Created by Dell on 23. 11. 2021.
//

#include "SequentialSuppressionNaive.h"

// class that computes serial resistance the most primitive way
// using naive backtrack generates all graphs with suppress edge operation
// and then for each of them checks if it is 3-edge-colorable
// does not even check for duplicate graphs
// useful as benchmark when testing more sophisticated algorithms for computing serial resistance
std::vector<CubicGraph> SequentialSuppressionNaive::findSuppressionSequence(CubicGraph cubicGraph) {
    if(cubicGraph.isColorable()){
        return std::vector<CubicGraph>{cubicGraph};
    }

    unsigned int unique_id = cubicGraph.getId() +1;
    std::vector<CubicGraph> graphList;
    unsigned int i = 0;

    graphList.push_back(cubicGraph);
    bool coloringFound = false;

    while(i < graphList.size() && !coloringFound){
        for(auto e : graphList[i].getEdges()) {
            if(!e.isLoop()) {
                CubicGraph suppressedGraph = graphList[i].suppressEdge(unique_id, e);
                if (!suppressedGraph.isColorable()) {
                    graphList.push_back(suppressedGraph);
                    unique_id++;
                } else {
                    coloringFound = true;
                    graphList.push_back(suppressedGraph);
                    break;
                }
            }
        }
        i++;
    }
    return toSuppressionSequence(graphList);
}
