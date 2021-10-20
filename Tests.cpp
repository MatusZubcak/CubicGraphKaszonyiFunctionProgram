//
// Created by Dell on 12. 10. 2021.
//

#include <cassert>
#include <set>
#include <iostream>
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
    assert(cg1 == cg1);

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

    std::set<unsigned int> K4_vertices{1, 2, 3, 4};
    std::set<Edge> K4_edges{e12, e13, e14, e23, e24, e34};
    CubicGraph K4(K4_vertices, K4_edges);
    CubicGraph K4_firstSuppression = K4.suppressEdge(1,2);
    Edge K4_firstSuppression_expectedEdge(3,4);
    assert(K4 == K4);

    K4_firstSuppression_expectedEdge.incrementMultiplicity();
    K4_firstSuppression_expectedEdge.incrementMultiplicity();
    std::set<unsigned int> K4_firstSuppression_expectedVertices{3,4};
    std::set<Edge> K4_firstSuppression_expectedEdges{K4_firstSuppression_expectedEdge};
    CubicGraph K4_firstSuppression_expectedGraph(K4_firstSuppression_expectedVertices, K4_firstSuppression_expectedEdges);

    assert(K4_firstSuppression.getVertices() == K4_firstSuppression_expectedVertices);
    assert(K4_firstSuppression.getEdges() == K4_firstSuppression_expectedEdges);
    assert(K4_firstSuppression == K4_firstSuppression_expectedGraph);
    assert(K4_firstSuppression.getDepth() == 1);

    CubicGraph K4_secondSuppression = K4_firstSuppression.suppressEdge(3,4);
    std::set<unsigned int> K4_secondSuppression_expectedVertices{};
    std::set<Edge> K4_secondSuppression_expectedEdges{};
    unsigned int K4_secondSuppression_ExpectedNumberOfIsolatedCircles = 1;
    CubicGraph K4_secondSuppression_expectedGraph(K4_secondSuppression_expectedVertices,
                                                  K4_secondSuppression_expectedEdges,
                                                  K4_secondSuppression_ExpectedNumberOfIsolatedCircles);
    assert(K4_secondSuppression == K4_secondSuppression_expectedGraph);
    assert(K4_secondSuppression.getDepth() == 2);

    std::set<unsigned int> test1_vertices = {1, 2, 11, 12, 21, 22};
    std::set<Edge> test1_edges = {Edge(1,2),
                                  Edge(1,11), Edge(1, 12),
                                  Edge(2, 21), Edge(2, 22)};
    CubicGraph test1_graph(test1_vertices, test1_edges);
    CubicGraph test1_suppressed = test1_graph.suppressEdge(1,2);

    std::set<unsigned int> test1_expectedVertices{11, 12, 21, 22};
    std::set<Edge> test1_expectedEdges{Edge(11,12), Edge(21, 22)};
    CubicGraph test1_expectedGraph(test1_expectedVertices, test1_expectedEdges);
    assert(test1_suppressed == test1_expectedGraph);
    assert(test1_suppressed.getDepth() == 1);
    for(auto e : test1_suppressed.getEdges()){
        assert(e.getMultiplicity() == 1);
    }



    std::set<unsigned int> test2_vertices{1, 2, 3, 4};
    std::set<Edge> test2_edges{Edge(1,2), Edge(3,4)};
    Edge test2_edgeWithMultiplicity2(2,3);
    test2_edgeWithMultiplicity2.incrementMultiplicity();
    test2_edges.insert(test2_edgeWithMultiplicity2);
    CubicGraph test2_graph(test2_vertices, test2_edges);

    CubicGraph test2_suppressed = test2_graph.suppressEdge(2,3);
    std::set<unsigned int> test2_expectedVertices{1,4};
    std::set<Edge> test2_expectedEdges{Edge(1,4)};
    CubicGraph test2_expectedGraph(test2_expectedVertices, test2_expectedEdges);
    assert(test2_suppressed == test2_expectedGraph);
    assert(test2_suppressed.getDepth() == 1);
    for(auto e : test2_suppressed.getEdges()){
        assert(e.getMultiplicity() == 1);
    }



    std::set<unsigned int> test3_vertices{1, 2, 3, 4, 5};
    std::set<Edge> test3_edges{Edge(1,2), Edge(3,2),
                               Edge(2, 4)};
    Edge test3_edgeWithMultiplicity(4,5);
    test3_edgeWithMultiplicity.incrementMultiplicity();
    test3_edges.insert(test3_edgeWithMultiplicity);
    CubicGraph test3_graph(test3_vertices, test3_edges);

    CubicGraph test3_suppressed = test3_graph.suppressEdge(2,4);
    std::set<unsigned int> test3_expectedVertices{1,3,5};
    std::set<Edge> test3_expectedEdges{Edge(1,3), Edge(5,5)};
    CubicGraph test3_expectedGraph(test3_expectedVertices, test3_expectedEdges);
    assert(test3_expectedGraph.getVertices() == test3_suppressed.getVertices());
    assert(test3_expectedGraph.getEdges() == test3_suppressed.getEdges());
    assert(test3_suppressed == test3_expectedGraph);
    assert(test3_suppressed.getDepth() == 1);
    for(auto e : test3_suppressed.getEdges()){
        assert(e.getMultiplicity() == 1);
    }

    std::set<unsigned int> test4_vertices{1, 2, 3, 4, 5};
    std::set<Edge> test4_edges{Edge(3,2),
                               Edge(3, 4),
                               Edge(3, 5)};
    Edge test4_edgeWithMultiplicity(1,2);
    test4_edgeWithMultiplicity.incrementMultiplicity();
    test4_edges.insert(test4_edgeWithMultiplicity);
    CubicGraph test4_graph(test4_vertices, test4_edges);

    CubicGraph test4_suppressed = test4_graph.suppressEdge(2,3);
    std::set<unsigned int> test4_expectedVertices{1,4,5};
    std::set<Edge> test4_expectedEdges{Edge(4, 5), Edge(1,1)};
    CubicGraph test4_expectedGraph(test4_expectedVertices, test4_expectedEdges);
    assert(test4_expectedGraph.getVertices() == test4_suppressed.getVertices());
    assert(test4_expectedGraph.getEdges() == test4_suppressed.getEdges());
    assert(test4_suppressed == test4_expectedGraph);
    assert(test4_suppressed.getDepth() == 1);
    for(auto e : test4_suppressed.getEdges()){
        assert(e.getMultiplicity() == 1);
    }


    std::set<unsigned int> test5_vertices{1, 2, 3, 4};
    std::set<Edge> test5_edges{Edge(1,1), Edge(1,2),
                               Edge(2,3), Edge(2,4)};
    CubicGraph test5_graph(test5_vertices, test5_edges);

    CubicGraph test5_suppressed = test5_graph.suppressEdge(1,2);
    std::set<unsigned int> test5_expectedVertices{3,4};
    std::set<Edge> test5_expectedEdges{Edge(3,4)};
    CubicGraph test5_expectedGraph(test5_expectedVertices, test5_expectedEdges, 1);
    assert(test5_expectedGraph.getVertices() == test5_suppressed.getVertices());
    assert(test5_expectedGraph.getEdges() == test5_suppressed.getEdges());
    assert(test5_suppressed == test5_expectedGraph);
    assert(test5_suppressed.getDepth() == 1);
    for(auto e : test5_suppressed.getEdges()){
        assert(e.getMultiplicity() == 1);
    }

    std::set<unsigned int> test6_vertices{1, 2, 3, 4};
    std::set<Edge> test6_edges{Edge(1,3), Edge(3,2),
                               Edge(4,4), Edge(3,4)};
    CubicGraph test6_graph(test6_vertices, test6_edges);

    CubicGraph test6_suppressed = test6_graph.suppressEdge(3,4);
    std::set<unsigned int> test6_expectedVertices{1,2};
    std::set<Edge> test6_expectedEdges{Edge(1,2)};
    CubicGraph test6_expectedGraph(test6_expectedVertices, test6_expectedEdges, 1);
    assert(test6_suppressed == test6_expectedGraph);
    assert(test6_suppressed.getDepth() == 1);
    for(auto e : test6_suppressed.getEdges()){
        assert(e.getMultiplicity() == 1);
    }

    std::set<unsigned int> test7_vertices{1,2,3,4};
    std::set<Edge> test7_edges{Edge(1,3), Edge(2,4)};
    Edge t7_e12(1,2);
    t7_e12.incrementMultiplicity();
    Edge t7_e34(3,4);
    t7_e34.incrementMultiplicity();
    test7_edges.insert(t7_e12);
    test7_edges.insert(t7_e34);
    CubicGraph test7_graph(test7_vertices, test7_edges);

    CubicGraph test7_suppressed = test7_graph.suppressEdge(1,2);
    std::set<unsigned int> test7_expectedVertices{3,4};
    std::set<Edge> test7_expectedEdges{};
    Edge t7_expectedEdge34(3,4);
    t7_expectedEdge34.incrementMultiplicity();
    t7_expectedEdge34.incrementMultiplicity();
    test7_expectedEdges.insert(t7_expectedEdge34);
    CubicGraph test7_expectedGraph(test7_expectedVertices, test7_expectedEdges);
    assert(test7_suppressed == test7_expectedGraph);
    assert(test7_suppressed.getEdges().find(Edge(3,4))->getMultiplicity() == 3);
    assert(test7_suppressed.getDepth() == 1);



    std::set<unsigned int> test8to14_vertices{1,2, 11, 12, 21, 22};
    std::set<unsigned int> test8to14_expectedVertices{11, 12, 21, 22};
    std::set<Edge> test8to14_commonEdges{Edge(1, 2),
                                         Edge(1, 11), Edge(1, 12),
                                         Edge(2, 21), Edge(2, 22)};

    std::set<Edge> test8_edges = test8to14_commonEdges;
    test8_edges.insert(Edge(11,12));
    test8_edges.insert(Edge(21, 22));
    CubicGraph test8_graph(test8to14_vertices, test8_edges);

    CubicGraph test8_suppressed = test8_graph.suppressEdge(1,2);
    std::set<Edge> test8_expectedEdges;
    Edge t8e11_12(11,12);
    Edge t8e21_22(21,22);
    t8e11_12.incrementMultiplicity();
    t8e21_22.incrementMultiplicity();
    test8_expectedEdges.insert(t8e11_12);
    test8_expectedEdges.insert(t8e21_22);
    CubicGraph test8_expectedGraph(test8to14_expectedVertices, test8_expectedEdges);
    assert(test8_suppressed == test8_expectedGraph);

    std::set<Edge> test9_edges = test8to14_commonEdges;
    test9_edges.insert(Edge(11, 21));
    test9_edges.insert(Edge(12,22));
    CubicGraph test9_graph(test8to14_vertices, test9_edges);

    CubicGraph test9_suppressed = test9_graph.suppressEdge(1,2);
    std::set<Edge> test9_expectedEdges{Edge(11, 12), Edge(11, 21),
                                       Edge(12, 22), Edge(21, 22)};
    CubicGraph test9_expectedGraph(test8to14_expectedVertices, test9_expectedEdges);
    assert(test9_suppressed == test9_expectedGraph);

    std::set<Edge> test10_edges = test8to14_commonEdges;
    test10_edges.insert(Edge(11, 21));
    test10_edges.insert(Edge(11, 22));
    test10_edges.insert(Edge(12, 21));
    test10_edges.insert(Edge(12, 22));
    CubicGraph test10_graph(test8to14_vertices, test10_edges);

    CubicGraph test10_suppressed = test10_graph.suppressEdge(1,2);
    std::set<Edge> test10_expectedEdges{Edge(11, 12), Edge(21, 22),
                                        Edge(11, 21), Edge(11, 22),
                                        Edge(12, 21), Edge(12, 22)};
    CubicGraph test10_expectedGraph(test8to14_expectedVertices, test10_expectedEdges);
    assert(test10_suppressed == test10_expectedGraph);

    std::set<Edge> test11_edges = test8to14_commonEdges;
    Edge t11e11_21(11,21);
    Edge t11e12_22(12,22);
    t11e11_21.incrementMultiplicity();
    t11e12_22.incrementMultiplicity();
    test11_edges.insert(t11e12_22);
    test11_edges.insert(t11e11_21);
    CubicGraph test11_graph(test8to14_vertices, test11_edges);

    CubicGraph test11_suppressed = test11_graph.suppressEdge(1,2);
    std::set<Edge> test11_expectedEdges{Edge(11, 12), Edge(21, 22)};
    test11_expectedEdges.insert(t11e11_21);
    test11_expectedEdges.insert(t11e12_22);
    CubicGraph test11_expectedGraph(test8to14_expectedVertices, test11_expectedEdges);
    assert(test11_suppressed == test11_expectedGraph);

    std::set<Edge> test12_edges = test8to14_commonEdges;
    Edge t12e11_12(11,12);
    Edge t12e21_22(21,22);
    t12e11_12.incrementMultiplicity();
    t12e21_22.incrementMultiplicity();
    test12_edges.insert(t12e21_22);
    test12_edges.insert(t12e11_12);
    CubicGraph test12_graph(test8to14_vertices, test12_edges);

    CubicGraph t12_suppressed = test12_graph.suppressEdge(1,2);
    std::set<Edge> test12_expectedEdges;
    Edge t12e11_12_expected(11,12);
    Edge t12e21_22_expected(21, 22);
    for(int i = 0; i < 2; i++){
        t12e11_12_expected.incrementMultiplicity();
        t12e21_22_expected.incrementMultiplicity();
    }
    test12_expectedEdges.insert(t12e21_22_expected);
    test12_expectedEdges.insert(t12e11_12_expected);
    CubicGraph test12_expectedGraph(test8to14_expectedVertices, test12_expectedEdges);
    assert(t12_suppressed == test12_expectedGraph);

    std::set<Edge> test13_edges = test8to14_commonEdges;
    test13_edges.insert(Edge(11,12));
    test13_edges.insert(Edge(21,22));
    test13_edges.insert(Edge(11,21));
    test13_edges.insert(Edge(12,22));
    CubicGraph test13_graph(test8to14_vertices, test13_edges);

    CubicGraph test13_suppressed = test13_graph.suppressEdge(1,2);
    std::set<Edge> test13_expectedEdges{Edge(11, 21), Edge(12, 22)};
    Edge t13e11_12_expected(11,12);
    Edge t13e21_22_expected(21,22);
    t13e11_12_expected.incrementMultiplicity();
    t13e21_22_expected.incrementMultiplicity();
    test13_expectedEdges.insert(t13e21_22_expected);
    test13_expectedEdges.insert(t13e11_12_expected);
    CubicGraph test13_expectedGraph(test8to14_expectedVertices, test13_expectedEdges);
    assert(test13_suppressed == test13_expectedGraph);

    std::set<Edge> test14_edges = test8to14_commonEdges;
    test14_edges.insert(Edge(21, 21));
    CubicGraph test14_graph(test8to14_vertices, test14_edges);

    CubicGraph test14_suppressed = test14_graph.suppressEdge(1,2);
    std::set<Edge> test14_expectedEdges{Edge(11, 12),
                                        Edge(21, 22),
                                        Edge(21, 21)};
    CubicGraph test14_expectedGraph(test8to14_expectedVertices, test14_expectedEdges);
    assert(test14_suppressed == test14_expectedGraph);

    std::cout << "ALL TESTS PASSED" << std::endl;
    return 0;
}
