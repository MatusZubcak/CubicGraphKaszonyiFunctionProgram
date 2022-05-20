//
// Created by Matus on 25. 10. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_COLORINGFINDER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_COLORINGFINDER_H

#include <set>
#include "../Edge.h"

// Interface for 3-edge-coloring algorithms

class ColoringFinder{

public:
    virtual int computeColorings(std::set<unsigned int>& vertices,
                                 std::set<Edge>& edges,
                                 unsigned int numberOfIsolatedCircles) = 0;
    virtual int computeColorings(std::set<unsigned int>& vertices,
                                 std::set<Edge>& edges) = 0;
    virtual bool isColorable(std::set<unsigned int>& vertices,
                             std::set<Edge>& edges) = 0;
    virtual ~ColoringFinder()= default;;

};

#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_COLORINGFINDER_H
