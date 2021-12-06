//
// Created by Dell on 18. 10. 2021.
//

#include <iostream>
#include "CubicGraph.h"
#include "KaszonyiFactorFunction.h"


CubicGraph::CubicGraph(unsigned int id, std::set<unsigned int> &vertices, std::set<Edge> &edges, unsigned int numberOfIsolatedCircles) {
    this->unique_id = id;
    this->parent_id = 0;
    this->depth = 0;
    this->vertices = vertices;
    this->edges = edges;
    this->numberOfIsolatedCircles = numberOfIsolatedCircles;
    strategy = std::shared_ptr<KaszonyiFunction>(new KaszonyiFactorFunction());

    for(auto e : edges){
        if( vertices.find(e.getIncidentvertices().first) == vertices.end() ||
            vertices.find(e.getIncidentvertices().second) == vertices.end()){
            throw BadlyDefinedGraphException();
        }
    }

}

CubicGraph::CubicGraph(unsigned int id, std::set<unsigned int> &vertices, std::set<Edge> &edges) : CubicGraph(id, vertices, edges, 0) {}
CubicGraph::CubicGraph(std::set<unsigned int> &vertices, std::set<Edge> &edges, unsigned int numberOfIsolatedCircles) : CubicGraph(0, vertices, edges, numberOfIsolatedCircles) {}
CubicGraph::CubicGraph(std::set<unsigned int> &vertices, std::set<Edge> &edges) : CubicGraph(0,vertices, edges, 0) {};


std::set<Edge> CubicGraph::getEdges() {
    return edges;
}

std::set<unsigned int> CubicGraph::getVertices() {
    return vertices;
}

unsigned int CubicGraph::size() {
    return vertices.size();
}

unsigned int CubicGraph::getNumberOfIsolatedCircles() const {
    return numberOfIsolatedCircles;
}

unsigned int CubicGraph::getDepth() const{
    return depth;
}

unsigned int CubicGraph::getId() const{
    return unique_id;
}

unsigned int CubicGraph::getParentId() const{
    return parent_id;
}

unsigned int CubicGraph::getKaszonyiValue(Edge edge) {
    if(edges.find(edge) == edges.end()){
        throw EdgeDoesNotExistException();
    }

    if(edges.find(edge)->isLoop()){
        Edge edgeToBeUpdated = *edges.find(edge);
        edgeToBeUpdated.setKaszonyiValue(0);
        edges.erase(edge);
        edges.insert(edgeToBeUpdated);
    }

    if(!edges.find(edge)->isLoop() && edges.find(edge)->getKaszonyiValue() == -1){
        Edge edgeToBeUpdated = *edges.find(edge);
        CubicGraph suppressedGraph = this->suppressEdge(edge);
        edgeToBeUpdated.setKaszonyiValue
            (this->strategy->getKaszonyiValue(suppressedGraph.vertices,
                                              suppressedGraph.edges,
                                              suppressedGraph.numberOfIsolatedCircles));

        edges.erase(edge);
        edges.insert(edgeToBeUpdated);
    }

    return edges.find(edge)->getKaszonyiValue();
}

bool operator==(const CubicGraph &cg1, const CubicGraph &cg2) {
    if (cg1.numberOfIsolatedCircles != cg2.numberOfIsolatedCircles ||
        cg1.vertices != cg2.vertices ||
        cg1.edges.size() != cg2.edges.size()) {
        return false;
    }

    for(auto it1 = cg1.edges.begin(), it2 = cg2.edges.begin();
        it1 != cg1.edges.end() || it2 != cg2.edges.end();
        ++it1, ++it2){
        if(*it1 != *it2 || it1->getMultiplicity() != it2->getMultiplicity()) {
            return false;
        }
    }

    return true;
}


bool operator!=(const CubicGraph &cg1, const CubicGraph &cg2) {
    return !(cg1 == cg2);
}
CubicGraph CubicGraph::suppressEdge(unsigned int id, Edge edge) {
    if(edges.find(edge) == edges.end()){
        throw EdgeDoesNotExistException();
    }
    Edge suppressedEdge = *edges.find(edge);
    //loop can't be suppressed
    if(suppressedEdge.isLoop()){
        throw LoopSuppressionException();
    }

    switch(suppressedEdge.getMultiplicity()){
        case 1:
            return suppressEdgeWithMultiplicity1(id, suppressedEdge);
        case 2:
            return suppressEdgeWithMultiplicity2(id, suppressedEdge);
        case 3:
            return suppressEdgeWithMultiplicity3(id, suppressedEdge);
    }
}

CubicGraph CubicGraph::suppressEdge(unsigned int id, unsigned int v1, unsigned int v2) {
    return suppressEdge(id, Edge(v1, v2));
}

CubicGraph CubicGraph::suppressEdge(Edge edge) {
    return suppressEdge(0, edge);
}

CubicGraph CubicGraph::suppressEdge(unsigned int v1, unsigned int v2) {
    return suppressEdge(0, v1, v2);
}

//PRIVATE FUNCTIONS

void CubicGraph::addEdge(Edge e) {
    if(e.isLoop() && vertices.find(e.getIncidentvertices().first) == vertices.end()){
            numberOfIsolatedCircles++;
    }
    else{
        if(edges.find(e) == edges.end()) {
            edges.insert(e);
        }else {
            Edge incrementedEdge = *edges.find(e);
            incrementedEdge.incrementMultiplicity();
            edges.erase(e);
            edges.insert(incrementedEdge);
        }
    }
}

std::set<unsigned int> CubicGraph::verticesAfterSuppressedEdge(Edge edge) {
    std::set<unsigned int> newVertices = vertices;
    newVertices.erase(edge.getIncidentvertices().first);
    newVertices.erase(edge.getIncidentvertices().second);

    return newVertices;
}

CubicGraph CubicGraph::suppressEdgeWithMultiplicity1(unsigned int id, Edge edge) {
    /* has to be removed because we don't want to FOR through
    * suppressed edge, it causes bugs
    * don't forget to add edge to edges in the end,
    * because edges belongs to original immutable graph
    */
    edges.erase(edge);

    std::set<unsigned int> newVertices = verticesAfterSuppressedEdge(edge);
    std::set<Edge> newEdges;

    unsigned int v1 = edge.getIncidentvertices().first;
    unsigned int v2 = edge.getIncidentvertices().second;
    std::pair<unsigned int, unsigned int> v1Neighbours;
    bool v1FirstNeighbourFound = false;
    std::pair<unsigned int, unsigned int> v2Neighbours;
    bool v2FirstNeighbourFound = false;

    for(auto e : edges){
        //case when edge incident with v1 is multiple edge
        if(e.isIncidentWith(v1) && e.getMultiplicity() == 2){
            v1Neighbours.first = e.getSecondVertex(v1);
            v1Neighbours.second = e.getSecondVertex(v1);
            v1FirstNeighbourFound = true;
        }
        //case when edge incident with v1 is loop
        else if(e.isIncidentWith(v1) && e.isLoop()){
            v1Neighbours = e.getIncidentvertices();
            v1FirstNeighbourFound = true;
        }
        //default case for edge incident with v1
        else if(e.isIncidentWith(v1)){
            if(v1FirstNeighbourFound){
                v1Neighbours.second = e.getSecondVertex(v1);
            } else{
                v1Neighbours.first = e.getSecondVertex(v1);
                v1FirstNeighbourFound = true;
            }
        }
        //case when edge incident with v2 is multiple edge
        else if(e.isIncidentWith(v2) && e.getMultiplicity() == 2){
            v2Neighbours.first = e.getSecondVertex(v2);
            v2Neighbours.second = e.getSecondVertex(v2);
            v2FirstNeighbourFound = true;
        }
        //case when edge incident with v2 is loop
        else if(e.isIncidentWith(v2) && e.isLoop()){
            v2Neighbours = e.getIncidentvertices();
            v2FirstNeighbourFound = true;
        }
        //default case for edge incident with v2
        else if(e.isIncidentWith(v2)){
            if(v2FirstNeighbourFound){
                v2Neighbours.second = e.getSecondVertex(v2);
            } else{
                v2Neighbours.first = e.getSecondVertex(v2);
                v2FirstNeighbourFound = true;
            }
        }
        //case when edge is not incident with any of v1, v2,
        //therefore is not affected by suppression
        else{
            newEdges.insert(e);
        }
    }

    CubicGraph newGraph(newVertices, newEdges, numberOfIsolatedCircles);

    //here we also solve isolatedCircles
    // new Edge is not original -> isOriginal = false
    newGraph.addEdge(Edge(v1Neighbours, false));
    newGraph.addEdge(Edge(v2Neighbours, false));

    //set depth, unique_id and parent_id
    newGraph.unique_id = id;
    newGraph.parent_id = this->unique_id;
    newGraph.depth = this->depth + 1;

    /* has to be added back again,
     * because it was temporarily removed
     * in the beginning of this function
     */
    edges.insert(edge);
    return newGraph;
}

CubicGraph CubicGraph::suppressEdgeWithMultiplicity2(unsigned int id, Edge edge) {
    /* has to be removed because we don't want to FOR through
    * suppressed edge, it causes bugs
    * don't forget to add edge to edges in the end,
    * because edges belongs to original immutable graph
    */
    edges.erase(edge);
    std::set<unsigned int> newVertices = verticesAfterSuppressedEdge(edge);
    std::set<Edge> newEdges;

    unsigned int v1 = edge.getIncidentvertices().first;
    unsigned int v2 = edge.getIncidentvertices().second;
    unsigned int v1Neighbour;
    unsigned int v2Neighbour;

    for(auto e : edges){
        if(e.isIncidentWith(v1)){
            v1Neighbour = e.getSecondVertex(v1);
        }
        else if(e.isIncidentWith(v2)){
            v2Neighbour = e.getSecondVertex(v2);
        } else{
            newEdges.insert(e);
        }
    }

    CubicGraph newGraph(newVertices, newEdges, numberOfIsolatedCircles);
    //here we also solve isolatedCircles
    // new Edge is not original -> isOriginal = false
    newGraph.addEdge(Edge(v1Neighbour, v2Neighbour, false));

    //set depth, unique_id and parent_id
    newGraph.unique_id = id;
    newGraph.parent_id = this->unique_id;
    newGraph.depth = this->depth + 1;

    /* has to be added back again,
     * because it was temporarily removed
     * in the beginning of this function
     */
    edges.insert(edge);
    return newGraph;
}

CubicGraph CubicGraph::suppressEdgeWithMultiplicity3(unsigned int id, Edge edge) {
    std::set<unsigned int> newVertices = verticesAfterSuppressedEdge(edge);
    std::set<Edge> newEdges = edges;
    newEdges.erase(edge);

    CubicGraph newGraph(newVertices, newEdges, numberOfIsolatedCircles + 1);

    //set depth, unique_id and parent_id
    newGraph.unique_id = id;
    newGraph.parent_id = this->unique_id;
    newGraph.depth = this->depth + 1;

    return newGraph;
}