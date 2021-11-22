//
// Created by Dell on 3. 11. 2021.
//

#include <iostream>
#include <fstream>
#include "GraphPrinterSemestralProjectFormat.h"

std::vector<std::pair<unsigned int, bool>>
GraphPrinterSemestralProjectFormat::getLinearGraphRepresentation(CubicGraph &cubicGraph) {

    std::vector<std::pair<unsigned int, bool>>linearGraphRepresentation
            (3*cubicGraph.size(), std::pair<int,bool>(0, true));

    for(auto e : cubicGraph.getEdges()){
        unsigned int v1 = e.getIncidentvertices().first;
        unsigned int v2 = e.getIncidentvertices().second;
        unsigned int v1VectorIndex = 3*v1;
        unsigned int v2VectorIndex = 3*v2;

        for(int repeats = 0; repeats < e.getMultiplicity(); repeats++) {
            for (unsigned int i = v1VectorIndex; i < v1VectorIndex + 3; i++) {
                if (linearGraphRepresentation[i].second) {
                    linearGraphRepresentation[i].first = v2;
                    linearGraphRepresentation[i].second = false;
                    break;
                }
            }
            for (unsigned int i = v2VectorIndex; i < v2VectorIndex + 3; i++) {
                if (linearGraphRepresentation[i].second) {
                    linearGraphRepresentation[i].first = v1;
                    linearGraphRepresentation[i].second = false;
                    break;
                }
            }
        }
    }
    return linearGraphRepresentation;
}

bool GraphPrinterSemestralProjectFormat::printGraph(CubicGraph &cubicGraph, const std::string &filename,
                                                    append append) {
    std::ofstream f;
    if(append == APPEND)
        f.open(filename, std::ios::app);
    else
        f.open(filename);

    try{
        if (!f) {
            throw FileCannotBeOpenedException();
        }
        std::vector<std::pair<unsigned int, bool>> linearGraphRepresentation = getLinearGraphRepresentation(cubicGraph);
        std::set<unsigned int> vertices = cubicGraph.getVertices();

        for(int i = 0; i < cubicGraph.size(); i++){
            f << linearGraphRepresentation[3*i].first << " "
              << linearGraphRepresentation[3*i+1].first << " "
              << linearGraphRepresentation[3*i+2].first
              << std::endl;
        }

        f.close();
    }catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }
    return true;
}


bool GraphPrinterSemestralProjectFormat::printKaszonyiValue_forSingleEdge(CubicGraph &cubicGraph, const std::string &filename,
                                                                   Edge edge,
                                                                   append append) {
    std::ofstream f;
    if(append == APPEND)
        f.open(filename, std::ios::app);
    else
        f.open(filename);

    try{
        if (!f) {
            throw FileCannotBeOpenedException();
        }
        f << "potlacena hrana: ( "
          << edge.getIncidentvertices().first
          << ", "
          << edge.getIncidentvertices().second
          << " )    hodnota psi: "
          << cubicGraph.getKaszonyiValue(edge)
          << std::endl;
        f.close();
    }catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }
    return true;
}

bool GraphPrinterSemestralProjectFormat::printKaszonyiValue_forAllEdges(CubicGraph &cubicGraph, const std::string &filename,
                                                                 append append) {
    std::ofstream f;
    if(append == APPEND)
        f.open(filename, std::ios::app);
    else
        f.open(filename);

    try{
        if (!f) {
            throw FileCannotBeOpenedException();
        }
        for(auto e : cubicGraph.getEdges()) {
            f << "potlacena hrana: ( "
              << e.getIncidentvertices().first
              << ", "
              << e.getIncidentvertices().second
              << " )    hodnota psi: "
              << cubicGraph.getKaszonyiValue(e)
              << std::endl;
        }
        f.close();
    }catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }
    return true;
}


