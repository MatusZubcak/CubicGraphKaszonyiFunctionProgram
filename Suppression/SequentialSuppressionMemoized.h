//
// Created by Dell on 28. 1. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSIONMEMOIZED_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSIONMEMOIZED_H

#include "Suppression.h"

// class that computes serial resistance using some kind of memoization
// generates all graphs with suppress edge operation
// and then for each of them checks if it is 3-edge-colorable
//
// only computes if the graph is 3-edge-colorable once for the same graphs
// first its checks if it has not already computed 3-edge-colorability for the given graph using memoization table
class SequentialSuppressionMemoized : public Suppression {
public:
    std::vector<CubicGraph> findSuppressionSequence(CubicGraph cubicGraph) override;

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SEQUENTIALSUPPRESSIONMEMOIZED_H
