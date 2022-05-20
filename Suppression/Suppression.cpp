//
// Created by Dell on 29. 1. 2022.
//

#include "Suppression.h"

// converts queue of all graphs that have been generated during the computation of parallel/serial resistance
// to graph suppression sequence (first = original graph, last = edge-3-colorable graph
std::vector<CubicGraph>
Suppression::toSuppressionSequence(const std::vector<CubicGraph> &graphList) {

    const unsigned int first_id = graphList.front().getId();
    const unsigned int size = graphList.back().getDepth() - graphList.front().getDepth() + 1;

    unsigned int id = graphList.back().getId();
    unsigned int i = size - 1;
    std::vector<CubicGraph> suppressionSequence(size);

    while(id != first_id){
        suppressionSequence[i] = graphList[id - first_id];
        id = graphList[id - first_id].getParentId();
        i--;
    }
    suppressionSequence[i] = graphList[id - first_id];

    if(i != 0){
        throw ConversionFromListToSequenceFailed();
    }
    return suppressionSequence;
}

