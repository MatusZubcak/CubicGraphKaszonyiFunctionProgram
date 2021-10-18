//
// Created by Dell on 12. 10. 2021.
//

#include <cassert>
#include <set>
#include "Tests.h"
#include "Edge.h"
#include "CubicGraph.h"

int Tests::run(){

    Edge e12(1, 2);
    Edge e13(1, 3);
    Edge e14(4, 1);
    Edge e23(2, 3);
    Edge e24(2, 4);
    Edge e34(3, 4);
    Edge e14_another(1, 4);

    assert(e12.getIncidentvertices().first == 1);
    assert(e12.getIncidentvertices().second == 2);
    assert(e14.getIncidentvertices().first == 1);
    assert(e14.getIncidentvertices().second == 4);

    assert(e12.toString() == "(1, 2)");
    assert(e14.toString() == "(1, 4)");

    assert(e14 == e14_another);
    assert(e14 != e24);
    assert(e12 < e14);
    assert(e13 > e12);
    assert(e24 > e12);
    assert(e13 < e24);
    assert(e14 <= e14_another);
    assert(e14 >= e14_another);
    assert(e12 <= e14);
    assert(e13 >= e12);
    assert(e24 >= e12);
    assert(e13 <= e24);

    e12.setKaszonyiValue(7);
    assert(e12.getKaszonyiValue() == 7);

    assert(e12.getMultiplicity() == 1);
    e12.incrementMultiplicity();
    assert(e12.getMultiplicity() == 2);
    e12.incrementMultiplicity();
    assert(e12.getMultiplicity() == 3);
    e12.decrementMultiplicity();
    assert(e12.getMultiplicity() == 2);
    e12.decrementMultiplicity();
    assert(e12.getMultiplicity() == 1);

    std::set<unsigned int> testVertices1 = {
            0, 1, 5, 7, 10
    };

    std::set<Edge> testEdges1 ={
            Edge(0,5), Edge(1, 7), Edge(10, 0),
            Edge(0,1), Edge(5,7), Edge(10,1)
    };

    CubicGraph cg1(testVertices1, testEdges1, 0);
    assert(cg1.getVertices() == testVertices1);
    assert(cg1.getEdges() == testEdges1);

    Edge e12_another (std::pair<unsigned int, unsigned int>(1, 2));
    assert(e12_another == e12);

    Edge e11(1, 1);
    assert(e11.isLoop());
    assert(!e12.isLoop());

    assert(e11.getSecondVertex(1) == 1);
    assert(e12.getSecondVertex(2) == 1);
    assert(e12.getSecondVertex(1) == 2);
    assert(e12.isIncidentWith(1));
    assert(e12.isIncidentWith(2));
    assert(!e12.isIncidentWith(3));


    //assert(0 == 1);
    return 0;
}