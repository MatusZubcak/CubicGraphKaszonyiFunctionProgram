//
// Created by Dell on 22. 11. 2021.
//

#include <vector>
#include <iostream>
#include <unordered_map>
#include "GraphPrinter.h"

std::vector<std::pair<unsigned int, bool>>
GraphPrinter::getLinearGraphRepresentation(CubicGraph &cubicGraph) {

    auto edges = cubicGraph.getEdges();
    std::vector<unsigned int> vertices;
    std::unordered_map<unsigned int, unsigned int> map_vertex_index;
    unsigned int index = 0;
    for(auto v : cubicGraph.getVertices()){
        vertices.push_back(v);
        map_vertex_index[v] = index;
        index++;
    }
    std::set<Edge> wellIndexedEdges;
    for(auto e : edges){
        unsigned int v1 = e.getIncidentvertices().first;
        unsigned int v2 = e.getIncidentvertices().second;
        Edge wellIndexedEdge = Edge(map_vertex_index[v1], map_vertex_index[v2]);
        for(int i = 1; i < e.getMultiplicity(); i++){
            wellIndexedEdge.incrementMultiplicity();
        }
        wellIndexedEdges.insert(wellIndexedEdge);
    }

    std::vector<std::pair<unsigned int, bool>>linearGraphRepresentation
            (3*cubicGraph.size(), std::pair<int,bool>(0, true));

    for(auto e : wellIndexedEdges){
        unsigned int v1 = e.getIncidentvertices().first;
        unsigned int v2 = e.getIncidentvertices().second;
        unsigned int v1VectorIndex = 3*v1;
        unsigned int v2VectorIndex = 3*v2;

        for(int repeats = 0; repeats < e.getMultiplicity(); repeats++) {
            for (unsigned int i = v1VectorIndex; i < v1VectorIndex + 3; i++) {
                if (linearGraphRepresentation[i].second) {
                    linearGraphRepresentation[i].first = vertices[v2];
                    linearGraphRepresentation[i].second = false;
                    break;
                }
            }
            for (unsigned int i = v2VectorIndex; i < v2VectorIndex + 3; i++) {
                if (linearGraphRepresentation[i].second) {
                    linearGraphRepresentation[i].first = vertices[v1];
                    linearGraphRepresentation[i].second = false;
                    break;
                }
            }
        }
    }
    return linearGraphRepresentation;
}

