//
// Created by Dell on 23. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CONTINUOUSSUPPRESSION_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CONTINUOUSSUPPRESSION_H

#include <queue>
#include "CubicGraph.h"

class ContinuousSuppression{
public:
    virtual std::queue<CubicGraph> findDepth(const CubicGraph& cubicGraph) =0;
};

#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CONTINUOUSSUPPRESSION_H
