//
// Created by Dell on 12. 10. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_EDGE_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_EDGE_H


#include <utility>
#include <string>
#include "GraphExceptions.h"


// class that represents edge in a cubic graph
// we choose this design because we want to know different information about the edges in the graph
// quickly and without much pain
// most of it was required to program edge suppression while still remaining relatively legible,
// catching all possible cases and without bugs
// we have also wanted to store multiple edges as a single edge (good for edge suppression)
// edge_isOriginal is also useful information when comuputing parallel resistance
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

    std::pair<unsigned int, unsigned int> getIncidentvertices() const;

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
