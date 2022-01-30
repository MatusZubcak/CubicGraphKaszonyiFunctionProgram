//
// Created by Dell on 28. 1. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSIONMEMOIZED_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSIONMEMOIZED_H

#include "ContinuousSuppression.h"

class SequentialSuppressionMemoized : ContinuousSuppression {
public:
    std::vector<CubicGraph> findSuppressionSequence(const CubicGraph& cubicGraph) override;

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSIONMEMOIZED_H
