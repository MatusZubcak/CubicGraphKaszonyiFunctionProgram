//
// Created by Dell on 23. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSIONNAIVE_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSIONNAIVE_H

#include "ContinuousSuppression.h"

class SequentialSuppressionNaive : ContinuousSuppression {

public:
    std::vector<CubicGraph> findSuppressionSequence(CubicGraph cubicGraph) override;
};

#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSIONNAIVE_H
