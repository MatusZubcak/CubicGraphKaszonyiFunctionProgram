//
// Created by Dell on 28. 1. 2022.
//

#include <cstddef>
#include <cmath>
#include <algorithm>
#include <unordered_set>
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

//Edge -> hash (used when edge is added to set)
struct EdgeHash{

    std::size_t operator()(const Edge&  edge) const noexcept
    {
        unsigned int x = edge.getIncidentvertices().first;
        unsigned int y = edge.getIncidentvertices().second;

        return (x*x + 3*x + 2*x*y + y + y*y)/2;
    }
};

struct MapOfProcessedVerticesHash{

    std::size_t operator()(const std::set<std::pair<unsigned int, unsigned int>>& processedVerticesMap) const noexcept
    {
        std::size_t seed = processedVerticesMap.size();
        for(const auto& item : processedVerticesMap){
            seed ^= ((item.second*2) + 3) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;

    }
};