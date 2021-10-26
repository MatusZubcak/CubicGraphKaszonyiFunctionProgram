//
// Created by Dell on 25. 10. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_KASZONYIFACTORFUNCTION_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_KASZONYIFACTORFUNCTION_H


#include <vector>
#include <unordered_map>
#include <set>
#include "Edge.h"
#include "KaszonyiFunction.h"

class KaszonyiFactorFunction : public KaszonyiFunction {

private:
    int kaszonyiValue;

    void reccursivellyCountKaszonyi(std::vector<std::pair<unsigned int,bool>> linearGraphRepresentation,
                                    unsigned int vertex);

    bool cycleIsEven(std::vector<std::pair<unsigned int, bool>> &linearGraphRepresentation,
                     unsigned int vertex);

    std::vector<std::pair<unsigned int,bool>> convertToLinearGraphRepresentation(
                std::set<unsigned int>& vertices, std::set<Edge>& edges);

public:
    KaszonyiFactorFunction();

    int getKaszonyiValue(std::set<unsigned int>& vertices,
                         std::set<Edge>& edges,
                         unsigned int numberOfIsolatedCircles) override;

    int getKaszonyiValue(std::set<unsigned int>& vertices,
                                 std::set<Edge>& edges) override;

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_KASZONYIFACTORFUNCTION_H
