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
    unsigned int unique_id{};
    unsigned int parent_id{};
    unsigned int depth{};
    std::set<unsigned int> vertices;
    std::set<Edge> edges;
    unsigned int numberOfIsolatedCircles{};
    std::shared_ptr<KaszonyiFunction> strategy;

    void addEdge(Edge e);
    CubicGraph suppressEdgeWithMultiplicity1(unsigned int id, Edge edge);
    CubicGraph suppressEdgeWithMultiplicity2(unsigned int id, Edge edge);
    CubicGraph suppressEdgeWithMultiplicity3(unsigned int id, Edge edge);
    std::set<unsigned int> verticesAfterSuppressedEdge(Edge edge);

    friend bool operator==(const CubicGraph& cg1, const CubicGraph& cg2);
    friend bool operator!=(const CubicGraph& cg1, const CubicGraph& cg2);

public:
    CubicGraph(unsigned int id, std::set<unsigned int>& vertices, std::set<Edge>& edges, unsigned int numberOfIsolatedCircles);
    CubicGraph(unsigned int id, std::set<unsigned int>& vertices, std::set<Edge>& edges);
    CubicGraph(std::set<unsigned int>& vertices, std::set<Edge>& edges, unsigned int numberOfIsolatedCircles);
    CubicGraph(std::set<unsigned int>& vertices, std::set<Edge>& edges);
    CubicGraph()= default;

    std::set<Edge> getEdges();

    std::set<unsigned int> getVertices();

    unsigned int size();

    unsigned int getNumberOfIsolatedCircles() const;

    unsigned int getDepth() const;

    unsigned int getId() const;

    unsigned int getParentId() const;

    unsigned int getKaszonyiValue(Edge edge);

    CubicGraph suppressEdge(unsigned int id, Edge edge);
    CubicGraph suppressEdge(Edge edge);
    CubicGraph suppressEdge(unsigned int id, unsigned int v1, unsigned int v2);
    CubicGraph suppressEdge(unsigned int v1, unsigned int v2);

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CUBICGRAPH_H
