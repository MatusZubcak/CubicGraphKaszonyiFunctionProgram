//
// Created by Dell on 1. 2. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_COLORINGFINDERSAT_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_COLORINGFINDERSAT_H

#include "ColoringFinder.h"
#include <map>
#include <vector>
#include "cryptominisat.h"

class ColoringFinderSAT : public ColoringFinder {
private:
    std::map<unsigned int, std::vector<unsigned int>> toIncidenceIndexMap(const std::set<unsigned int> &vertices,
                                                                          const std::set<Edge> &edges);
    void toSATFormula(const std::set<unsigned int> &vertices, const std::set<Edge> &edges,
                      CMSat::SATSolver &satSolver);

public:
    ColoringFinderSAT()= default;;

    int computeColorings(std::set<unsigned int> &vertices, std::set<Edge> &edges) override;
    int computeColorings(std::set<unsigned int> &vertices, std::set<Edge> &edges,
                         unsigned int numberOfIsolatedCircles) override;
    bool isColorable(std::set<unsigned int> &vertices, std::set<Edge> &edges) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_COLORINGFINDERSAT_H
