//
// Created by Dell on 18. 10. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CUBICGRAPH_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CUBICGRAPH_H


#include <set>
#include <memory>
#include "Edge.h"
#include "ColoringFinder/ColoringFinder.h"

// class that represents cubic graph as an ordered set of vertices and Edges
// takes care for the edge suppression operation
// delegated 3-edge-colorability to strategy algorithm
//
// it is recommended not to choose 3-edge-colorabily strategy, so the class can use
// its own heuristics to choose the optimal algorithm itself (based on the size of the graph)
class CubicGraph {
private:
    unsigned int unique_id{};
    unsigned int parent_id{};
    unsigned int depth{};
    std::set<unsigned int> vertices;
    std::set<Edge> edges;
    unsigned int numberOfIsolatedCircles{};
    std::shared_ptr<ColoringFinder> coloringStrategy;
    bool preserveStrategy;

    void addEdge(Edge e);
    CubicGraph suppressEdgeWithMultiplicity1(unsigned int id, Edge edge);
    CubicGraph suppressEdgeWithMultiplicity2(unsigned int id, Edge edge);
    CubicGraph suppressEdgeWithMultiplicity3(unsigned int id, Edge edge);
    std::set<unsigned int> verticesAfterSuppressedEdge(Edge edge);

    friend bool operator==(const CubicGraph& cg1, const CubicGraph& cg2);
    friend bool operator!=(const CubicGraph& cg1, const CubicGraph& cg2);

public:
    CubicGraph(unsigned int id, std::set<unsigned int>& vertices, std::set<Edge>& edges,
               unsigned int numberOfIsolatedCircles, std::shared_ptr<ColoringFinder> &coloringStrategy);
    CubicGraph(unsigned int id, std::set<unsigned int>& vertices, std::set<Edge>& edges,
               std::shared_ptr<ColoringFinder> &coloringStrateg);
    CubicGraph(std::set<unsigned int>& vertices, std::set<Edge>& edges, unsigned int numberOfIsolatedCircles,
               std::shared_ptr<ColoringFinder> &coloringStrategy);
    CubicGraph(std::set<unsigned int>& vertices, std::set<Edge>& edges,
               std::shared_ptr<ColoringFinder> &coloringStrategy);

    CubicGraph(unsigned int id, std::set<unsigned int>& vertices, std::set<Edge>& edges,
               unsigned int numberOfIsolatedCircles);
    CubicGraph(unsigned int id, std::set<unsigned int>& vertices, std::set<Edge>& edges);
    CubicGraph(std::set<unsigned int>& vertices, std::set<Edge>& edges, unsigned int numberOfIsolatedCircles);
    CubicGraph(std::set<unsigned int>& vertices, std::set<Edge>& edges);
    CubicGraph()= default;

    std::set<Edge> getEdges() const;
    std::set<unsigned int> getVertices() const;

    unsigned int size() const;

    unsigned int getNumberOfIsolatedCircles() const;

    unsigned int getDepth() const;

    unsigned int getId() const;

    unsigned int getParentId() const;


    unsigned int getKaszonyiValue(Edge edge);
    bool isColorable();

    CubicGraph suppressEdge(unsigned int id, Edge edge);
    CubicGraph suppressEdge(Edge edge);
    CubicGraph suppressEdge(unsigned int id, unsigned int v1, unsigned int v2);
    CubicGraph suppressEdge(unsigned int v1, unsigned int v2);

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_CUBICGRAPH_H
