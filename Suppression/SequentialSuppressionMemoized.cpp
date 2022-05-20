//
// Created by Dell on 28. 1. 2022.
//

#include <unordered_set>
#include <iostream>
#include "SequentialSuppressionMemoized.h"
#include "../Hash.h"

// class that computes serial resistance using some kind of memoization
// generates all graphs with suppress edge operation
// and then for each of them checks if it is 3-edge-colorable
//
// only computes if the graph is 3-edge-colorable once for the same graphs
// first its checks if it has not already computed 3-edge-colorability for the given graph using memoization table
std::vector<CubicGraph> SequentialSuppressionMemoized::findSuppressionSequence(CubicGraph cubicGraph) {
    if(cubicGraph.isColorable()){
        return std::vector<CubicGraph>{cubicGraph};
    }

    unsigned int unique_id = cubicGraph.getId() +1;
    std::vector<CubicGraph> graphList;
    unsigned int i = 0;

    graphList.push_back(cubicGraph);
    bool coloringFound = false;

    std::unordered_set<CubicGraph, GraphHash> memoization_table;

    while(i < graphList.size() && !coloringFound){

        if(memoization_table.find(graphList[i]) == memoization_table.end()) {
            memoization_table.insert(graphList[i]);

            for (auto e : graphList[i].getEdges()) {
                if (!e.isLoop()) {
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

        }

        i++;
    }
    return toSuppressionSequence(graphList);
}