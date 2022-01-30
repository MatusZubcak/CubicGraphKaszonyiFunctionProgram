//
// Created by Dell on 23. 11. 2021.
//

#include "ParallelSuppressionNaive.h"

std::vector<CubicGraph> ParallelSuppressionNaive::findSuppressionSequence(const CubicGraph &cubicGraph) {
    unsigned long long unique_id = cubicGraph.getId() + 1;

    std::vector<CubicGraph> graphList;
    unsigned int i = 0;
    graphList.push_back(cubicGraph);
    bool coloringFound = false;

    while (i < graphList.size() && !coloringFound) {

        for (auto e : graphList[i].getEdges()) {
            if (e.isOriginal()) {
                if (!e.isLoop()) {
                    CubicGraph suppressedGraph = graphList[i].suppressEdge(unique_id, e);
                    if (!suppressedGraph.isColorable()) {
                        graphList.push_back(suppressedGraph);
                        unique_id++;
                    } else {
                        coloringFound = true;
                        graphList.push_back(suppressedGraph);
                        break;
                    }
                }
            }
        }
        i++;
    }
    return toSuppressionSequence(graphList);
}