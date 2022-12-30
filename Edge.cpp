//
// Created by Dell on 12. 10. 2021.
//

#include "Edge.h"

// class that represents edge in a cubic graph
// we choose this design because we want to know different information about the edges in the graph
// quickly and without much pain
// most of it was required to program edge suppression while still remaining relatively legible,
// catching all possible cases and without bugs
// we have also wanted to store multiple edges as a single edge (good for edge suppression)
// edge_isOriginal is also useful information when computing parallel resistance
Edge::Edge(unsigned int vertex1, unsigned int vertex2, bool isOriginal) :
    incidentVertices ( std::min(vertex1, vertex2), std::max(vertex1, vertex2)){

    this->multiplicity = 1;
    this->original = isOriginal;
}

Edge::Edge(unsigned int vertex1, unsigned int vertex2) : Edge(vertex1, vertex2, true) {};
Edge::Edge(std::pair<unsigned int, unsigned int> vertices, bool isOriginal) : Edge(vertices.first, vertices.second, isOriginal) {}

std::pair<unsigned int, unsigned int> Edge::getIncidentvertices() const{
    return incidentVertices;
}

// Edge to std::String in format (v_1, v_2) where v_1,v_2 are incident vertices lexicographically ordered
std::string Edge::toString() const {
    return "(" + std::to_string(incidentVertices.first) + ", " + std::to_string(incidentVertices.second) + ")";
}

// increment edge multiplicity (up to 3)
void Edge::incrementMultiplicity(){
    if(multiplicity < 3) {
        multiplicity++;
    } else{
        throw EdgeMaximalMultiplicityException();
    }
}

//decrement edge multiplicity (min 1)
void Edge::decrementMultiplicity() {
    if(multiplicity > 1){
        multiplicity--;
    } else{
        throw EdgeMinimalMultiplicityException();
    }
}

// get edge multiplicity
int Edge::getMultiplicity() const {
    return multiplicity;
}


// comparison operators
// useful when you want to know if the given as parameter is equal with some edge in the graph
// also useful when you have ordered set of edges, so you can loop through them lexicographically
bool operator==(const Edge &e1, const Edge &e2) {
    return (e1.incidentVertices.first == e2.incidentVertices.first &&
            e1.incidentVertices.second == e2.incidentVertices.second);
}

bool operator!=(const Edge &e1, const Edge &e2) {
    return (e1.incidentVertices.first != e2.incidentVertices.first ||
            e1.incidentVertices.second != e2.incidentVertices.second);
}

bool operator<(const Edge &e1, const Edge &e2) {
    if( e1.incidentVertices.first != e2.incidentVertices.first)
        return e1.incidentVertices.first < e2.incidentVertices.first;

    return e1.incidentVertices.second < e2.incidentVertices.second;
}

bool operator>(const Edge &e1, const Edge &e2) {
    if( e1.incidentVertices.first != e2.incidentVertices.first)
        return e1.incidentVertices.first > e2.incidentVertices.first;

    return e1.incidentVertices.second > e2.incidentVertices.second;
}

bool operator<=(const Edge &e1, const Edge &e2) {
    if(e1 == e2)
        return true;
    return e1 < e2;
}

bool operator>=(const Edge &e1, const Edge &e2) {
    if(e1 == e2)
        return true;

    return e1 > e2;
}

// is edge incident with vertex?
bool Edge::isIncidentWith(unsigned int vertex) const {
    if(incidentVertices.first == vertex || incidentVertices.second == vertex){
        return true;
    }
    return false;
}

// for proper edge returns second vertex
// for loop it crashes -> so you want to test if edge is loop first
unsigned int Edge::getSecondVertex(unsigned int vertex) const {
    if(incidentVertices.first == vertex){
        return incidentVertices.second;
    } else if(incidentVertices.second == vertex){
        return  incidentVertices.first;
    }

    throw VertexNotIncidentException();
}

// tests whether edge is loop
bool Edge::isLoop() const {
    return incidentVertices.first == incidentVertices.second;
}

// tests whether edge is from the original graph -> useful when computing parallel resistance
bool Edge::isOriginal() const{
    return original;
}