//
// Created by Dell on 29. 1. 2022.
//

#include "ContinuousSuppression.h"

std::vector<CubicGraph>
ContinuousSuppression::toSuppressionSequence(const std::vector<CubicGraph> &graphList) {

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

