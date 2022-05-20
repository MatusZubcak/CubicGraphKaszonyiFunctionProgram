//
// Created by Dell on 23. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PARALLELSUPPRESSIONNAIVE_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PARALLELSUPPRESSIONNAIVE_H

// class that computes parallel resistance the most primitive way
// using naive backtrack generates all graphs with suppress edge operation (only on original edges)
// and then for each of them checks if it is 3-edge-colorable
// does not even check for duplicate graphs
// useful as benchmark when testing more sophisticated algorithms for computing parallel resistance
#include "../CubicGraph.h"
#include "Suppression.h"

class ParallelSuppressionNaive : public Suppression {
public:
    std::vector<CubicGraph> findSuppressionSequence(CubicGraph cubicGraph) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PARALLELSUPPRESSIONNAIVE_H
