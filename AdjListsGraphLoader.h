//
// Created by Dell on 28. 10. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_ADJLISTSGRAPHLOADER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_ADJLISTSGRAPHLOADER_H


#include <queue>
#include "GraphLoader.h"

class AdjListsGraphLoader : public GraphLoader {
private:
    std::queue<CubicGraph> graphList;

    std::queue<CubicGraph> loadGraphs(const std::string& filename);
    void insertEdgeWithMultiplicity (std::set<Edge>& edges,
                                     unsigned int vertex,
                                     unsigned int multipleNeighbour,
                                     unsigned int singleNeighbour);
    bool correctlyDefinedGraph(std::set<unsigned int>& vertices, std::set<Edge>& edges);

public:
    explicit AdjListsGraphLoader(const std::string& filename);
    CubicGraph nextGraph() override;
    bool hasNext() override;
    bool loadNewGraphs(const std::string& filename) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_ADJLISTSGRAPHLOADER_H
