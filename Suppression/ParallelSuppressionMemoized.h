//
// Created by Dell on 29. 1. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PARALLELSUPPRESSIONMEMOIZED_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PARALLELSUPPRESSIONMEMOIZED_H

#include "Suppression.h"

class ParallelSuppressionMemoized : public Suppression {
public:
    std::vector<CubicGraph> findSuppressionSequence(CubicGraph cubicGraph) override;

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PARALLELSUPPRESSIONMEMOIZED_H
