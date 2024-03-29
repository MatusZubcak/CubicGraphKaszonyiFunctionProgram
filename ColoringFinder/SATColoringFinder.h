//
// Created by Dell on 1. 2. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SATCOLORINGFINDER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SATCOLORINGFINDER_H

#include "ColoringFinder.h"
#include <map>
#include <vector>
#include "../CMSat/cryptominisat.h"

// 3-edge-coloring finder based on CMSAT Solver by Mate Soos

class SATColoringFinder : public ColoringFinder {
private:
    std::map<unsigned int, std::vector<unsigned int>> toIncidenceIndexMap(const std::set<unsigned int> &vertices,
                                                                          const std::set<Edge> &edges);
    void toSATFormula(const std::set<unsigned int> &vertices, const std::set<Edge> &edges,
                      CMSat::SATSolver &satSolver);

public:
    SATColoringFinder()= default;;

    boost::multiprecision::int1024_t computeColorings(std::set<unsigned int> &vertices, std::set<Edge> &edges) override;
    boost::multiprecision::int1024_t computeColorings(std::set<unsigned int> &vertices, std::set<Edge> &edges,
                         unsigned int numberOfIsolatedCircles) override;
    bool isColorable(std::set<unsigned int> &vertices, std::set<Edge> &edges) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_SATCOLORINGFINDER_H
