//
// Created by Dell on 12. 10. 2021.
//

#include "Edge.h"

Edge::Edge(unsigned int vertex1, unsigned int vertex2, bool isOriginal) :
    incidentVertices ( std::min(vertex1, vertex2), std::max(vertex1, vertex2)){

    this->multiplicity = 1;
    this->original = isOriginal;
}

Edge::Edge(unsigned int vertex1, unsigned int vertex2) : Edge(vertex1, vertex2, true) {};
Edge::Edge(std::pair<unsigned int, unsigned int> vertices, bool isOriginal) : Edge(vertices.first, vertices.second, isOriginal) {}

std::pair<unsigned int, unsigned int> Edge::getIncidentvertices() {
    return incidentVertices;
}

std::string Edge::toString() const {
    return "(" + std::to_string(incidentVertices.first) + ", " + std::to_string(incidentVertices.second) + ")";
}

void Edge::incrementMultiplicity(){
    if(multiplicity < 3) {
        multiplicity++;
    } else{
        throw EdgeMaximalMultiplicityException();
    }
}

void Edge::decrementMultiplicity() {
    if(multiplicity > 1){
        multiplicity--;
    } else{
        throw EdgeMinimalMultiplicityException();
    }
}

int Edge::getMultiplicity() const {
    return multiplicity;
}

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

bool Edge::isIncidentWith(unsigned int vertex) const {
    if(incidentVertices.first == vertex || incidentVertices.second == vertex){
        return true;
    }
    return false;
}

unsigned int Edge::getSecondVertex(unsigned int vertex) const {
    if(incidentVertices.first == vertex){
        return incidentVertices.second;
    } else if(incidentVertices.second == vertex){
        return  incidentVertices.first;
    }

    throw VertexNotIncidentException();
}

bool Edge::isLoop() const {
    return incidentVertices.first == incidentVertices.second;
}

bool Edge::isOriginal() const{
    return original;
}