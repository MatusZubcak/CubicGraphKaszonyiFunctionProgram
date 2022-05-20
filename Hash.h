//
// Created by Dell on 28. 1. 2022.
//

#include <cstddef>
#include "CubicGraph.h"

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_HASH_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_HASH_H

#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_HASH_H

//Graph -> hash (used when graph is added to map)
struct GraphHash{

    std::size_t operator()(const CubicGraph&  graph) const noexcept
    {
        std::string edgeString;
        for(auto v : graph.getVertices()){
            edgeString += std::to_string(v);
        }
        std::hash<std::string> hash;
        return hash(edgeString);
    }
};