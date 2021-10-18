//
// Created by Dell on 18. 10. 2021.
//

#include "CubicGraph.h"
#include "GraphExceptions.h"

CubicGraph::CubicGraph(std::set<unsigned int> &vertices, std::set<Edge> &edges) {
    this->vertices = vertices;
    this->edges = edges;
    depth = 0;

    for(auto e : edges){
        if( vertices.find(e.getIncidentvertices().first) == vertices.end() ||
            vertices.find(e.getIncidentvertices().second) == vertices.end()){
            throw BadlyDefinedGraphException();
        }
    }

}

std::set<Edge> CubicGraph::getEdges() {
    return edges;
}

std::set<unsigned int> CubicGraph::getVertices() {
    return vertices;
}
