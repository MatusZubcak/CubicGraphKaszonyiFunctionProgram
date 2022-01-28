//
// Created by Dell on 23. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PARALLELSUPPRESSION_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PARALLELSUPPRESSION_H


#include "CubicGraph.h"
#include "ContinuousSuppression.h"

class ParallelSuppression : ContinuousSuppression {
public:
    std::vector<CubicGraph> findDepth(const CubicGraph& cubicGraph) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PARALLELSUPPRESSION_H
