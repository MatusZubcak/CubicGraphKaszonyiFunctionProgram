//
// Created by Dell on 23. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PARALLELSUPPRESSIONNAIVE_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PARALLELSUPPRESSIONNAIVE_H


#include "../CubicGraph.h"
#include "Suppression.h"

class ParallelSuppressionNaive : public Suppression {
public:
    std::vector<CubicGraph> findSuppressionSequence(CubicGraph cubicGraph) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PARALLELSUPPRESSIONNAIVE_H
