//
// Created by Dell on 29. 1. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PARALLELSUPPRESSIONMEMOIZED_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PARALLELSUPPRESSIONMEMOIZED_H

#include "ContinuousSuppression.h"

class ParallelSuppressionMemoized : ContinuousSuppression {
public:
    std::vector<CubicGraph> findSuppressionSequence(const CubicGraph& cubicGraph) override;

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PARALLELSUPPRESSIONMEMOIZED_H
