//
// Created by Dell on 23. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSIONNAIVE_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSIONNAIVE_H

#include "Suppression.h"

// class that computes serial resistance the most primitive way
// using naive backtrack generates all graphs with suppress edge operation
// and then for each of them checks if it is 3-edge-colorable
// does not even check for duplicate graphs
// useful as benchmark when testing more sophisticated algorithms for computing serial resistance
class SequentialSuppressionNaive : public Suppression {

public:
    std::vector<CubicGraph> findSuppressionSequence(CubicGraph cubicGraph) override;
};

#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSIONNAIVE_H
