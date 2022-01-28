//
// Created by Dell on 3. 11. 2021.
//

#include <iostream>
#include <fstream>
#include "GraphPrinterSemestralProjectFormat.h"

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

/*
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
}*/

bool GraphPrinterSemestralProjectFormat::printKaszonyiValues(CubicGraph &cubicGraph, const std::string &filename,
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

bool GraphPrinterSemestralProjectFormat::printKaszonyiValues(std::vector<CubicGraph> &graphList,
                                                             const std::string &filename,
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

        for(auto graph : graphList){

            std::vector<std::pair<unsigned int, bool>> linearGraphRepresentation =
                    getLinearGraphRepresentation(graph);
            std::set<unsigned int> vertices = graph.getVertices();

            auto it = vertices.begin();
            for(int i = 0; i < graph.size(); i++){
                f << linearGraphRepresentation[3*i].first << " "
                  << linearGraphRepresentation[3*i+1].first << " "
                  << linearGraphRepresentation[3*i+2].first
                  << std::endl;
                it++;
            }

            for(auto e : graph.getEdges()) {
                f << "potlacena hrana: ( "
                  << e.getIncidentvertices().first
                  << ", "
                  << e.getIncidentvertices().second
                  << " )    hodnota psi: "
                  << graph.getKaszonyiValue(e)
                  << std::endl;
            }
        }
        f << std::endl
          << std::endl;
        f.close();
    }catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }
    return true;

}


