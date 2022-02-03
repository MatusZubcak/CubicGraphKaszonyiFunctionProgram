//
// Created by Dell on 28. 10. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADERADJLISTS_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADERADJLISTS_H


#include <queue>
#include "GraphLoader.h"

class GraphLoaderAdjLists : public GraphLoader {
private:
    void insertEdgeWithMultiplicity (std::set<Edge>& edges,
                                     unsigned int vertex,
                                     unsigned int multipleNeighbour,
                                     unsigned int singleNeighbour);
    bool correctlyDefinedGraph(std::set<unsigned int>& vertices, std::set<Edge>& edges);

public:
    GraphLoaderAdjLists()= default;;
    std::vector<CubicGraph> loadNewGraphs(const std::string& filename) override;
    std::vector<CubicGraph> loadNewGraphs(const std::string &filename, coloringAlgorithm coloringAlgorithm) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADERADJLISTS_H
