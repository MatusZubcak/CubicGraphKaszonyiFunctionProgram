//
// Created by Dell on 22. 11. 2021.
//

#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "GraphPrinter.h"


bool GraphPrinter::printGraph(CubicGraph &cubicGraph, std::ofstream& f) {
    std::vector<std::vector<unsigned int>> adjacencyList = toAdjacencyList(cubicGraph);

    unsigned int i = 0;
    for(auto v : cubicGraph.getVertices()){
        f << adjacencyList[i][0] << " "
          << adjacencyList[i][1] << " "
          << adjacencyList[i][2]
          << std::endl;
        i++;
    }

    return true;
}

bool GraphPrinter::printGraphColorings(CubicGraph &cubicGraph, std::ofstream &f) {
    f << "Edge colorings: " << cubicGraph.getNumberOfColorings() << std::endl;

    return true;
}

bool GraphPrinter::printKaszonyiValues(CubicGraph& cubicGraph, std::ofstream& f, edgesFormat edgesFormat,
                                       colorPrintFormat colorPrintFormat){
    f << "Kaszonyi values:" << std::endl;

    for(auto e : cubicGraph.getEdges()){
        f << e.toString() << ": ";

        if(e.isLoop()){
            f << "LOOP";
        }else{
            if(colorPrintFormat == COLORING_EXISTS) {
                if (cubicGraph.suppressEdge(e).isColorable()) {
                    f << "Y";
                } else {
                    f << "N";
                }

            }else if (colorPrintFormat == COLORING_NUMBER_TIMES_THREE){
                f << cubicGraph.getKaszonyiValue(e);

            } else if (colorPrintFormat == COLORING_NUMBER_ORIGINAL){
                auto kaszonyiValue = cubicGraph.getKaszonyiValue(e);

                if(kaszonyiValue % 3 != 0){
                    throw KaszonyiValueNotDivisibleByThreeException();
                }else{
                    kaszonyiValue = kaszonyiValue / 3;
                    f << kaszonyiValue;
                }
            }
        }


        if(edgesFormat == MARK_ORIGINAL_EDGES && e.isOriginal()){
            f << "    Original";
        }
        f << std::endl;
    }

    return true;
}

bool GraphPrinter::printIdAndDepth(CubicGraph &cubicGraph, std::ofstream &f) {
    f << "Graph id: "
      << cubicGraph.getId()
      << std:: endl;
    f << "Parent id: "
      << cubicGraph.getParentId()
      << std::endl;
    f << "Depth: "
      << cubicGraph.getDepth()
      << std::endl;

    return true;
}

std::vector<std::vector<unsigned int>>
GraphPrinter::toAdjacencyList(CubicGraph &cubicGraph) {

    auto edges = cubicGraph.getEdges();
    std::vector<unsigned int> vertices;
    std::unordered_map<unsigned int, unsigned int> map_vertex_index;
    unsigned int index = 0;
    for(auto v : cubicGraph.getVertices()){
        vertices.push_back(v);
        map_vertex_index[v] = index;
        index++;
    }
    std::set<Edge> wellIndexedEdges;
    for(auto e : edges){
        unsigned int v1 = e.getIncidentvertices().first;
        unsigned int v2 = e.getIncidentvertices().second;
        Edge wellIndexedEdge = Edge(map_vertex_index[v1], map_vertex_index[v2]);
        for(int i = 1; i < e.getMultiplicity(); i++){
            wellIndexedEdge.incrementMultiplicity();
        }
        wellIndexedEdges.insert(wellIndexedEdge);
    }

    std::vector<std::vector<unsigned int>> adjacencyList
            (cubicGraph.size(), std::vector<unsigned int>(3));
    std::vector<std::vector<bool>> adjacencyList_freeSpaces
            (cubicGraph.size(), std::vector<bool>(3, true));

    for(auto e : wellIndexedEdges){
        unsigned int v1 = e.getIncidentvertices().first;
        unsigned int v2 = e.getIncidentvertices().second;

        for(int repeats = 0; repeats < e.getMultiplicity(); repeats++) {
            for (unsigned int i = 0; i < 3; i++) {
                if (adjacencyList_freeSpaces[v1][i]) {
                    adjacencyList[v1][i] = vertices[v2];
                    adjacencyList_freeSpaces[v1][i] = false;
                    break;
                }
            }
            for (unsigned int i = 0; i < 3; i++) {
                if (adjacencyList_freeSpaces[v2][i]) {
                    adjacencyList[v2][i] = vertices[v1];
                    adjacencyList_freeSpaces[v2][i] = false;
                    break;
                }
            }
        }
    }

    return adjacencyList;
}

