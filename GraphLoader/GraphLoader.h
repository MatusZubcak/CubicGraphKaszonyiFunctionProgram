//
// Created by Dell on 28. 10. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADER_H

#include <vector>
#include "../CubicGraph.h"
#include "../Enums.h"

// loads graphs in formats described in program instructions
class GraphLoader{
protected:
    void insertEdgeWithMultiplicity (std::set<Edge>& edges,
                                     unsigned int vertex,
                                     unsigned int multipleNeighbour,
                                     unsigned int singleNeighbour);
    bool correctlyDefinedGraph(const std::set<unsigned int>& vertices, const std::set<Edge>& edges);
    void loadGraph(std::vector<CubicGraph> &graphList, std::ifstream& f, unsigned int graph_size,
                   coloringAlgorithm coloringAlgorithm, const std::vector<unsigned int>& firstAdjList);
    bool loadNeighbours(std::ifstream& f, unsigned int& neighbour1, unsigned int& neighbour2, unsigned int& neighbour3);
    std::string loadAdditionalInformation(std::ifstream &f);

public:
    std::vector<CubicGraph> loadNewGraphs(const std::string& filename, std::vector<std::string>& informationFromFile);
    std::vector<CubicGraph> loadNewGraphs(const std::string& filename, std::vector<std::string>& informationFromFile,
                                                  coloringAlgorithm coloringAlgorithm);
    std::vector<CubicGraph> loadNewGraphs(const std::string& filename);
    std::vector<CubicGraph> loadNewGraphs(const std::string& filename, coloringAlgorithm coloringAlgorithm);
};

#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHLOADER_H
