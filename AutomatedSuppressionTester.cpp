//
// Created by Dell on 30. 1. 2022.
//

#include "AutomatedSuppressionTester.h"
#include "GraphLoaderAdjLists.h"
#include "SequentialSuppressionMemoized.h"
#include "SequentialSuppressionNaive.h"
#include "ParallelSuppressionMemoized.h"
#include "ParallelSuppressionNaive.h"

bool AutomatedSuppressionTester::testWithInputFile(const std::string &filename, suppression suppression,
                                                   unsigned int expectedDepth) {
    bool isCorrect = true;
    std::vector<CubicGraph> graphList = GraphLoaderAdjLists().loadNewGraphs(filename);

    for(const auto& graph : graphList){
        std::vector<CubicGraph> suppressionSequenceMemoized;
        std::vector<CubicGraph> suppressionSequenceNaive;

        if(suppression == SEQUENTIAL){
            suppressionSequenceMemoized = SequentialSuppressionMemoized().findSuppressionSequence(graph);
            suppressionSequenceNaive = SequentialSuppressionNaive().findSuppressionSequence(graph);
        } else if(suppression == PARALLEL){
            suppressionSequenceMemoized = ParallelSuppressionMemoized().findSuppressionSequence(graph);
            suppressionSequenceNaive = ParallelSuppressionNaive().findSuppressionSequence(graph);
        }

        isCorrect = validDepth(suppressionSequenceMemoized, suppressionSequenceNaive, expectedDepth) &&
                    validSequence(suppressionSequenceMemoized, suppression) &&
                    validSequence(suppressionSequenceNaive, suppression) &&
                    isCorrect;
    }
    return isCorrect;
}

bool AutomatedSuppressionTester::validDepth(const std::vector<CubicGraph> &suppressionSequenceMemoized,
                                            const std::vector<CubicGraph> &suppressionSequenceNaive,
                                            unsigned int expectedDepth) {
    return suppressionSequenceMemoized.back().getDepth() == expectedDepth &&
           suppressionSequenceNaive.back().getDepth() == expectedDepth;
}

bool AutomatedSuppressionTester::validSequence(std::vector<CubicGraph> &suppressionSequence, suppression suppression) {
    std::set<Edge> originalEdges = suppressionSequence.front().getEdges();

    for(int i = 0; i < suppressionSequence.size() - 1; i++){

        CubicGraph& currentGraph = suppressionSequence[i];
        CubicGraph& nextGraph = suppressionSequence[i+1];
        bool suppressionExists = false;

        for(auto edge : currentGraph.getEdges()){
            bool edge_isOriginal = originalEdges.find(edge) != originalEdges.end() &&
                                   edge.getMultiplicity() == originalEdges.find(edge)->getMultiplicity();

            if(suppression == SEQUENTIAL || (suppression == PARALLEL && edge_isOriginal)){
                if(currentGraph.suppressEdge(edge) == nextGraph){
                    suppressionExists = true;
                    break;
                }
            }
        }
        if(!suppressionExists){
            return false;
        }

    }
    return true;
}
