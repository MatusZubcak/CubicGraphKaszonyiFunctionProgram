//
// Created by Dell on 30. 1. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_AUTOMATEDSUPPRESSIONTESTER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_AUTOMATEDSUPPRESSIONTESTER_H


#include "Enums.h"
#include "CubicGraph.h"
#include <string>
#include <vector>

class AutomatedSuppressionTester {

public:
    bool testWithInputFile(const std::string& filename, suppression suppression, unsigned int expectedDepth);

private:
    bool validDepth(const std::vector<CubicGraph>& suppressionSequenceMemoized,
                    const std::vector<CubicGraph>& suppressionSequenceNaive,
                    unsigned int expectedDepth);

    bool validSequence(std::vector<CubicGraph>& suppressionSequence, suppression suppression);

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_AUTOMATEDSUPPRESSIONTESTER_H
