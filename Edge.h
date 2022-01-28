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
    int multiplicity;
    bool original;
    const std::pair<const unsigned int, const unsigned int> incidentVertices;

    friend bool operator==(const Edge& e1, const Edge& e2);
    friend bool operator!=(const Edge& e1, const Edge& e2);
    friend bool operator<(const Edge& e1, const Edge& e2);
    friend bool operator>(const Edge& e1, const Edge& e2);
    friend bool operator<=(const Edge& e1, const Edge& e2);
    friend bool operator>=(const Edge& e1, const Edge& e2);
public:

    Edge(unsigned int vertex1, unsigned int vertex2, bool isOriginal);
    Edge(std::pair<unsigned int, unsigned int> vertices, bool isOriginal);
    Edge(unsigned int vertex1,unsigned int vertex2);

    std::pair<unsigned int, unsigned int> getIncidentvertices();

    std::string toString() const;

    void incrementMultiplicity();

    void decrementMultiplicity();

    int getMultiplicity() const;

    bool isIncidentWith(unsigned int vertex) const;

    unsigned int getSecondVertex(unsigned int vertex) const;

    bool isLoop() const;

    bool isOriginal() const;

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_EDGE_H
