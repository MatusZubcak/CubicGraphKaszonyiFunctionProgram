//
// Created by matus on 18.10.2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PDCOLORINGFINDER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PDCOLORINGFINDER_H


#include <vector>
#include <unordered_set>
#include "ColoringFinder.h"
#include "../Hash.h"

class PDColoringFinder : public ColoringFinder{
private:
    std::set<unsigned int> vertices = {};
    std::set<Edge> edges = {};
    std::vector<std::vector<unsigned int>> adjLists = {};
    std::vector<std::vector<unsigned int>> components = {};
    std::vector<Edge> edgeOrdering = std::vector<Edge>();
    unsigned int startingVertex = 0;
    unsigned int pathDepth = 0;
    boost::multiprecision::int1024_t colorings = 0;

    bool addShortestHpath(std::unordered_set<unsigned int> &verticesInPathDecomposition,
                          std::unordered_set<Edge, EdgeHash> &edgesInPathDecomposition,
                          std::vector<Edge> &pathDecompositionEdgesOrdering,
                          unsigned int &pathDecompositionDepth);
    std::pair<unsigned int, std::vector<Edge>> findPathForComponent(unsigned int componentId);
    bool vertexInProgress(std::unordered_set<unsigned int> &verticesInPathDecomposition,
                          std::unordered_set<Edge, EdgeHash> &edgesInPathDecomposition,
                          unsigned int vertex);
    boost::multiprecision::int1024_t coloringAlgorithm();
    void setState(std::set<unsigned int> &vertices, std::set<Edge> &edges, bool &containsLoop);


public:

    PDColoringFinder()= default;;
    boost::multiprecision::int1024_t computeColorings(std::set<unsigned int> &vertices, std::set<Edge> &edges) override;
    boost::multiprecision::int1024_t computeColorings(std::set<unsigned int> &vertices, std::set<Edge> &edges,
                                        unsigned int numberOfIsolatedCircles) override;
    bool isColorable(std::set<unsigned int> &vertices, std::set<Edge> &edges) override;
    int findPathDecomposition();

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_PDCOLORINGFINDER_H
