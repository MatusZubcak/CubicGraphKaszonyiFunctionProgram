//
// Created by Dell on 28. 10. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADER_H

#include <vector>
#include "../CubicGraph.h"
#include "../Enums.h"

class GraphLoader{
protected:
    void insertEdgeWithMultiplicity (std::set<Edge>& edges,
                                     unsigned int vertex,
                                     unsigned int multipleNeighbour,
                                     unsigned int singleNeighbour);
    bool correctlyDefinedGraph(const std::set<unsigned int>& vertices, const std::set<Edge>& edges);
    bool loadGraph(std::vector<CubicGraph> &graphList, std::ifstream& f, unsigned int graph_size,
                   coloringAlgorithm coloringAlgorithm);
    bool loadNeighbours(std::ifstream& f, unsigned int& neighbour1, unsigned int& neighbour2, unsigned int& neighbour3);
    std::string loadAdditionalInformation(std::ifstream &f);

public:
    virtual std::vector<CubicGraph> loadNewGraphs(const std::string& filename, std::string& informationFromFile) = 0;
    virtual std::vector<CubicGraph> loadNewGraphs(const std::string& filename, std::string& informationFromFile,
                                                  coloringAlgorithm coloringAlgorithm) = 0;
    virtual std::vector<CubicGraph> loadNewGraphs(const std::string& filename) = 0;
    virtual std::vector<CubicGraph> loadNewGraphs(const std::string& filename, coloringAlgorithm coloringAlgorithm) = 0;
};

#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADER_H
