//
// Created by Dell on 30. 1. 2022.
//

#include <iostream>
#include "AutomatedSuppressionTester.h"
#include "GraphLoaderSimpleAdjListsFormat.h"
#include "SequentialSuppressionMemoized.h"
#include "SequentialSuppressionNaive.h"
#include "ParallelSuppressionMemoized.h"
#include "ParallelSuppressionNaive.h"
#include "GraphExceptions.h"

bool AutomatedSuppressionTester::testWithInputFile(const std::string &filename, suppression suppression,
                                                   std::vector<int> expectedDepthList) {
    bool isCorrect = true;
    std::vector<CubicGraph> graphList = GraphLoaderSimpleAdjListsFormat().loadNewGraphs(filename);

    if(graphList.size() != expectedDepthList.size()){
        throw ExpectedDepthListWrongSize();
    }

    for(int i = 0; i < graphList.size(); i++){
        CubicGraph& graph = graphList[i];
        int expectedDepth = expectedDepthList[i];
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

bool AutomatedSuppressionTester::validDepth(std::vector<CubicGraph> &suppressionSequenceMemoized,
                                            std::vector<CubicGraph> &suppressionSequenceNaive,
                                            int expectedDepth) {
    if(suppressionSequenceNaive.back().isColorable() != suppressionSequenceMemoized.back().isColorable()){
        return false;

    } else if(suppressionSequenceNaive.back().isColorable()){
        return suppressionSequenceMemoized.back().getDepth() == expectedDepth &&
               suppressionSequenceNaive.back().getDepth() == expectedDepth;

    } else{
        return expectedDepth == -1;
    }
}

bool AutomatedSuppressionTester::validSequence(std::vector<CubicGraph> &suppressionSequence, suppression suppression) {
    std::set<Edge> originalEdges = suppressionSequence.front().getEdges();

    for(int i = 0; i < suppressionSequence.size() - 1; i++){

        CubicGraph& currentGraph = suppressionSequence[i];
        CubicGraph& nextGraph = suppressionSequence[i+1];
        bool suppressionExists = false;

        for(auto edge : currentGraph.getEdges()){
            bool edge_isOriginal = originalEdges.find(edge) != originalEdges.end();

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
