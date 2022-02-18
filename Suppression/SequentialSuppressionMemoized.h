//
// Created by Dell on 28. 1. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSIONMEMOIZED_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSIONMEMOIZED_H

#include "Suppression.h"

class SequentialSuppressionMemoized : public Suppression {
public:
    std::vector<CubicGraph> findSuppressionSequence(CubicGraph cubicGraph) override;

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSIONMEMOIZED_H
