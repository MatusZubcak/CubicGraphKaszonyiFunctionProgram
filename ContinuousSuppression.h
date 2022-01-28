//
// Created by Dell on 23. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CONTINUOUSSUPPRESSION_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CONTINUOUSSUPPRESSION_H

#include "CubicGraph.h"
#include <vector>

class ContinuousSuppression{
public:
    virtual std::vector<CubicGraph> findDepth(const CubicGraph& cubicGraph) =0;
};

#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CONTINUOUSSUPPRESSION_H
