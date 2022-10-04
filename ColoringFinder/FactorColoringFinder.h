//
// Created by Dell on 25. 10. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_FACTORCOLORINGFINDER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_FACTORCOLORINGFINDER_H


#include <vector>
#include <unordered_map>
#include <set>
#include "../Edge.h"
#include "ColoringFinder.h"

// 3-edge-coloring finder based on equivalence of the 3-edge-coloring and
// a 1-factor and a set of cykles with even length
class FactorColoringFinder : public ColoringFinder {

private:
    int colorings;

    void recursivelyCountKaszonyi(std::vector<std::pair<unsigned int,bool>> linearGraphRepresentation,
                                    unsigned int vertex);

    bool cycleIsEven(std::vector<std::pair<unsigned int, bool>> &linearGraphRepresentation,
                     unsigned int vertex);

    std::vector<std::pair<unsigned int,bool>> convertToLinearGraphRepresentation(
                std::set<unsigned int>& vertices, std::set<Edge>& edges);

public:
    FactorColoringFinder();

    unsigned long long computeColorings(std::set<unsigned int>& vertices,
                         std::set<Edge>& edges,
                         unsigned int numberOfIsolatedCircles) override;

    unsigned long long computeColorings(std::set<unsigned int>& vertices,
                                 std::set<Edge>& edges) override;

    bool isColorable(std::set<unsigned int> &vertices, std::set<Edge> &edges) override;

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_FACTORCOLORINGFINDER_H
