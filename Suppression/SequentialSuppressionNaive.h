//
// Created by Dell on 23. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSIONNAIVE_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSIONNAIVE_H

#include "Suppression.h"

class SequentialSuppressionNaive : public Suppression {

public:
    std::vector<CubicGraph> findSuppressionSequence(CubicGraph cubicGraph) override;
};

#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSIONNAIVE_H
