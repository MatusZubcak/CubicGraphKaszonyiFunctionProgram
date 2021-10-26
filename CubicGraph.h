//
// Created by Dell on 18. 10. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CUBICGRAPH_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CUBICGRAPH_H


#include <set>
#include <memory>
#include "Edge.h"
#include "KaszonyiFunction.h"

class CubicGraph {
private:
    std::set<unsigned int> vertices;
    std::set<Edge> edges;
    unsigned int depth;
    unsigned int numberOfIsolatedCircles;
    std::shared_ptr<KaszonyiFunction> strategy;

    void addEdge(Edge e);
    CubicGraph suppressEdgeWithMultiplicity1(Edge edge);
    CubicGraph suppressEdgeWithMultiplicity2(Edge edge);
    CubicGraph suppressEdgeWithMultiplicity3(Edge edge);
    std::set<unsigned int> verticesAfterSuppressedEdge(Edge edge);

    friend bool operator==(const CubicGraph& cg1, const CubicGraph& cg2);
    friend bool operator!=(const CubicGraph& cg1, const CubicGraph& cg2);

public:
    CubicGraph(std::set<unsigned int>& vertices, std::set<Edge>& edges);
    CubicGraph(std::set<unsigned int>& vertices, std::set<Edge>& edges, unsigned int numberOfIsolatedCircles);

    std::set<Edge> getEdges();

    std::set<unsigned int> getVertices();

    unsigned int getNumberOfIsolatedCircles() const;

    unsigned int getDepth() const;

    unsigned int getKaszonyiValue(Edge edge);

    CubicGraph suppressEdge(Edge edge);
    CubicGraph suppressEdge(unsigned int v1, unsigned int v2);
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CUBICGRAPH_H
