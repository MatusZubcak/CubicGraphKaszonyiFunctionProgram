//
// Created by Dell on 23. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CONTINUOUSSUPPRESSION_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CONTINUOUSSUPPRESSION_H

#include "CubicGraph.h"
#include <vector>

class ContinuousSuppression{
public:
    virtual std::vector<CubicGraph> findSuppressionSequence(const CubicGraph& cubicGraph) =0;

protected:
    std::vector<CubicGraph> toSuppressionSequence(const std::vector<CubicGraph>& graphList);
};

#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CONTINUOUSSUPPRESSION_H
