//
// Created by Dell on 12. 10. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_EDGE_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_EDGE_H


#include <utility>
#include <string>
#include "GraphExceptions.h"

class Edge {

private:
    int kaszonyiValue;
    int multiplicity;
    const std::pair<const unsigned int, const unsigned int> incidentVertices;

    friend bool operator==(const Edge& e1, const Edge& e2);
    friend bool operator!=(const Edge& e1, const Edge& e2);
    friend bool operator<(const Edge& e1, const Edge& e2);
    friend bool operator>(const Edge& e1, const Edge& e2);
    friend bool operator<=(const Edge& e1, const Edge& e2);
    friend bool operator>=(const Edge& e1, const Edge& e2);
public:

    Edge(int vertex1, int vertex2);

    void setKaszonyiValue(int kaszonyiValue);

    int getKaszonyiValue() const;

    std::pair<int, int> getIncidentvertices();

    std::string toString() const;

    void incrementMultiplicity();

    void decrementMultiplicity();

    int getMultiplicity();

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_EDGE_H
