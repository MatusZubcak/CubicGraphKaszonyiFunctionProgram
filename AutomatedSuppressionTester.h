//
// Created by Dell on 30. 1. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_AUTOMATEDSUPPRESSIONTESTER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_AUTOMATEDSUPPRESSIONTESTER_H


#include "Enums.h"
#include "CubicGraph.h"
#include <string>
#include <vector>

// class that helps to test whether algorithms for parallel and sequential suppression return
// expected values and if the returned graph suppression sequence is valid
class AutomatedSuppressionTester {

public:
    bool testWithInputFile(const std::string& filename, suppression suppression, std::vector<int> expectedDepthList);

private:
    bool validDepth(std::vector<CubicGraph>& suppressionSequenceMemoized,
                    std::vector<CubicGraph>& suppressionSequenceNaive,
                    int expectedDepth);

    bool validSequence(std::vector<CubicGraph>& suppressionSequence, suppression suppression);

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_AUTOMATEDSUPPRESSIONTESTER_H
