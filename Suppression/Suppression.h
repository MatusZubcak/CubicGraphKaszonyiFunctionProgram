//
// Created by Dell on 23. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SUPPRESSION_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SUPPRESSION_H

#include "../CubicGraph.h"
#include <vector>

// interface for different parallel and serial resistance algorithms
class Suppression{
public:
    virtual std::vector<CubicGraph> findSuppressionSequence(CubicGraph cubicGraph) =0;

protected:
    std::vector<CubicGraph> toSuppressionSequence(const std::vector<CubicGraph>& graphList);
};

#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SUPPRESSION_H
