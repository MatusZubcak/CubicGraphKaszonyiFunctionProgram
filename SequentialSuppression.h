//
// Created by Dell on 23. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSION_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSION_H

#include "ContinuousSuppression.h"

class SequentialSuppression : ContinuousSuppression {

public:
    std::queue<CubicGraph> findDepth(const CubicGraph& cubicGraph) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSION_H
