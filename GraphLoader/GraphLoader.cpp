//
// Created by Dell on 4. 2. 2022.
//

#include "GraphLoader.h"
#include "../ColoringFinder/SATColoringFinder.h"
#include "../ColoringFinder/FactorColoringFinder.h"
#include "../ColoringFinder/PDColoringFinder.h"
#include <unordered_map>
#include <fstream>
#include <sstream>
// interface for different graph loaders
// also includes different functions that are reusable for now graph loaders
// currently only single graph loader class inherits from it but provides the possibility of extension in the future

// if you find out cubic graph has edge with multiplicity, you can insert it to the set of edges using this function
void GraphLoader::insertEdgeWithMultiplicity(std::set<Edge> &edges,
                                                                 unsigned int vertex,
                                                                 unsigned int multipleVertex,
                                                                 unsigned int singleVertex){
    Edge normalEdge(vertex, singleVertex);
    Edge edgeWithMultiplicity(vertex, multipleVertex);
    edgeWithMultiplicity.incrementMultiplicity();

    edges.insert(normalEdge);
    edges.insert(edgeWithMultiplicity);
}


// function that loads information in curly brackets - { }
// from the beginning of cubic graphs text file
std::string GraphLoader::loadAdditionalInformation(std::ifstream &f) {
    std::string informationString;
    std::string getline_str;

    while(f.peek() != '{'){
        if(!std::getline(f, getline_str)){
            break;
        }
    }
    getline_str.erase();

    while(f.peek() == '{'){
        std::getline(f, getline_str);
        informationString += getline_str + '\n';
    }

    return informationString;
}

// load neighbours of current vertex to u_int neighbour1,2,3 variables
bool GraphLoader::loadNeighbours(std::ifstream &f, unsigned int &neighbour1, unsigned int &neighbour2,
                                 unsigned int &neighbour3) {
    std::string buffer, word;
    std::vector<std::string> stringList;

    while(stringList.empty() && std::getline(f, buffer)) {
        std::stringstream stringStream(buffer);

        while (stringStream >> word) {
            stringList.push_back(word);
        }


        if (stringList.size() != 3 && !stringList.empty()) {
            throw WrongNumberOfVerticesException();
        } else if (stringList.size() == 3) {
            neighbour1 = std::stoul(stringList[0]);
            neighbour2 = std::stoul(stringList[1]);
            neighbour3 = std::stoul(stringList[2]);
        }
    }

    return !stringList.empty();
}

// function that checks whether the loaded graph is defined correctly
// e.g. is cubic, no oriented edges, every vertex is size <= graph.size, ...
bool GraphLoader::correctlyDefinedGraph(const std::set<unsigned int>& vertices,
                                        const std::set<Edge>& edges) {
    std::unordered_map<unsigned int, int> map_vertex_degree;
    for(int i = 0; i < vertices.size(); i++){
        map_vertex_degree[i] = 0;
    }
    for(auto e : edges){
        if (vertices.find(e.getIncidentvertices().first) == vertices.end())
            return false;
        else
            for(int j = 0; j < e.getMultiplicity(); j++){
                map_vertex_degree[e.getIncidentvertices().first]++;
            }


        if(vertices.find((e.getIncidentvertices().second)) == vertices.end())
            return false;
        else
            for(int j = 0; j < e.getMultiplicity(); j++) {
                map_vertex_degree[e.getIncidentvertices().second]++;
            }
    }

    for(auto v : map_vertex_degree){
        if(v.second != 3)
            return false;
    }

    return true;
}

// loads single graph from file in ifstream &f
bool GraphLoader::loadGraph(std::vector<CubicGraph> &graphList, std::ifstream &f, unsigned int graph_size,
                            coloringAlgorithm coloringAlgorithm) {
    unsigned int neighbour1 = 0,
                 neighbour2 = 0,
                 neighbour3 = 0;

    std::set<unsigned int> vertices;
    std::set<Edge> edges;
    for (int i = 0; i < graph_size; i++) {
        vertices.insert(vertices.end(), i);
    }

    for (int currentVertex = 0; currentVertex < graph_size; currentVertex++) {
        if(loadNeighbours(f, neighbour1, neighbour2, neighbour3)){
            if (neighbour1 == neighbour2 && neighbour1 == neighbour3) {
                Edge edgeWithMultiplicity3(currentVertex, neighbour1);
                edgeWithMultiplicity3.incrementMultiplicity();
                edgeWithMultiplicity3.incrementMultiplicity();

                edges.insert(edgeWithMultiplicity3);
            } else if (neighbour1 == neighbour2) {
                if (currentVertex != neighbour1) {
                    insertEdgeWithMultiplicity(edges, currentVertex,
                                               neighbour1,
                                               neighbour3);
                } else {
                    edges.insert(Edge(currentVertex, currentVertex));
                    edges.insert(Edge(currentVertex, neighbour3));
                }
            } else if (neighbour1 == neighbour3) {
                if (currentVertex != neighbour1) {
                    insertEdgeWithMultiplicity(edges, currentVertex,
                                               neighbour1,
                                               neighbour2);
                } else {
                    edges.insert(Edge(currentVertex, currentVertex));
                    edges.insert(Edge(currentVertex, neighbour2));
                }
            } else if (neighbour2 == neighbour3) {
                if (currentVertex != neighbour2) {
                    insertEdgeWithMultiplicity(edges, currentVertex,
                                               neighbour2,
                                               neighbour1);
                } else {
                    edges.insert(Edge(currentVertex, currentVertex));
                    edges.insert(Edge(currentVertex, neighbour1));
                }
            } else {
                Edge edgeWithNeighbour1(currentVertex, neighbour1);
                Edge edgeWithNeighbour2(currentVertex, neighbour2);
                Edge edgeWithNeighbour3(currentVertex, neighbour3);

                edges.insert(edgeWithNeighbour1);
                edges.insert(edgeWithNeighbour2);
                edges.insert(edgeWithNeighbour3);
            }
        } else if(currentVertex == 0){
            //There are no more graphs to be loaded
            return false;
        } else{
            //Some, but not enough vertices in file to load full graph
            throw BadFileEndingException();
        }
    }

    if(correctlyDefinedGraph(vertices, edges)){
        //Graph loaded successfully
        // time to add it to graphList
        std::shared_ptr<ColoringFinder> strategySAT = std::shared_ptr<ColoringFinder>(new SATColoringFinder);
        std::shared_ptr<ColoringFinder> strategyPD = std::shared_ptr<ColoringFinder>(new PDColoringFinder);
        std::shared_ptr<ColoringFinder> strategyFactor = std::shared_ptr<ColoringFinder>(new FactorColoringFinder);
        switch (coloringAlgorithm){
            case SAT:
                graphList.emplace_back(vertices, edges, strategySAT);
                break;
            case PD:
                graphList.emplace_back(vertices, edges, strategyPD);
                break;
            case FACTOR:
                graphList.emplace_back(vertices, edges, strategyFactor);
                break;
            default:
                graphList.emplace_back(vertices, edges);
        }

        return true;
    } else{
        throw BadlyDefinedGraphException();
    }
}