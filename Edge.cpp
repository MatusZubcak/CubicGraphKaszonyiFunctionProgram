//
// Created by Dell on 12. 10. 2021.
//

#include "Edge.h"

Edge::Edge(int vertex1, int vertex2) :
    incidentVertices ( std::min(vertex1, vertex2), std::max(vertex1, vertex2)){

    this->kaszonyiValue = -1;
    this->multiplicity = 1;
}

void Edge::setKaszonyiValue(int kaszonyiValue) {
    this->kaszonyiValue = kaszonyiValue;
}

int Edge::getKaszonyiValue() const {
    return kaszonyiValue;
}

std::pair<int, int> Edge::getIncidentvertices() {
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

int Edge::getMultiplicity() {
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