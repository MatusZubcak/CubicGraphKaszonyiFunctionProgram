//
// Created by Dell on 28. 10. 2021.
//

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include "AdjListsGraphLoader.h"

AdjListsGraphLoader::AdjListsGraphLoader(const std::string& filename) {
    graphList = loadGraphs(filename);
}

CubicGraph AdjListsGraphLoader::nextGraph() {
    if(graphList.empty()){
        throw GraphloaderEmptyException();
    }

    CubicGraph graph = graphList.front();
    graphList.pop();
    return graph;
}

bool AdjListsGraphLoader::hasNext() {
    return !graphList.empty();
}

std::queue<CubicGraph> AdjListsGraphLoader::loadGraphs(const std::string& filename) {
    std::queue<CubicGraph> graphQueue;
    std::ifstream f;
    f.open(filename);
    if (!f) {
        std::cerr << "Unable to open file " << filename;
        exit(1);   // call system to stop
    }

    unsigned int numberOfVertices;
    unsigned int neighbour1, neighbour2, neighbour3;
    /*Pokusi sa pomocou txt suboru vytvorit korektny kubicky graf */
    try {
        f >> numberOfVertices;
        if (numberOfVertices < 0) throw WrongNumberOfVerticesException();


        std::set<unsigned int> vertices;
        for (int i = 0; i < numberOfVertices; i++) {
            vertices.insert(vertices.end(), i);
        }
        std::set<Edge> edges;

        unsigned int currentVertex = 0;
        while (f >> neighbour1 >> neighbour2 >> neighbour3) {
            if (neighbour1 == neighbour2 && neighbour1 == neighbour3) {
                Edge edgeWithMultiplicity3(currentVertex, neighbour1);
                edgeWithMultiplicity3.incrementMultiplicity();
                edgeWithMultiplicity3.incrementMultiplicity();

                edges.insert(edgeWithMultiplicity3);
            } else if (neighbour1 == neighbour2) {
                if(currentVertex != neighbour1) {
                    insertEdgeWithMultiplicity(edges, currentVertex,
                                               neighbour1,
                                               neighbour3);
                }else{
                    edges.insert(Edge(currentVertex, currentVertex));
                    edges.insert(Edge(currentVertex, neighbour3));
                }
            } else if (neighbour1 == neighbour3) {
                if(currentVertex != neighbour1) {
                    insertEdgeWithMultiplicity(edges, currentVertex,
                                               neighbour1,
                                               neighbour2);
                }else{
                    edges.insert(Edge(currentVertex, currentVertex));
                    edges.insert(Edge(currentVertex, neighbour2));
                }
            } else if (neighbour2 == neighbour3) {
                if(currentVertex != neighbour2) {
                    insertEdgeWithMultiplicity(edges, currentVertex,
                                               neighbour2,
                                               neighbour1);
                }else{
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

            currentVertex++;
            if (currentVertex == numberOfVertices) {
                currentVertex = 0;
                if (!correctlyDefinedGraph(vertices, edges)) {
                    throw BadlyDefinedGraphException();
                }
                graphQueue.push(CubicGraph(vertices, edges));
                edges.clear();
            }
        }
        if(currentVertex == 0) {
            return graphQueue;
        }else {
            throw BadFileEndingException();
        }
    } catch (std::exception &e) {
        f.close();
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
    }


}

void AdjListsGraphLoader::insertEdgeWithMultiplicity(std::set<Edge> &edges,
                                                     unsigned int vertex,
                                                     unsigned int multipleVertex,
                                                     unsigned int singleVertex){
    Edge normalEdge(vertex, singleVertex);
    Edge edgeWithMultiplicity(vertex, multipleVertex);
    edgeWithMultiplicity.incrementMultiplicity();

    edges.insert(normalEdge);
    edges.insert(edgeWithMultiplicity);
}

bool AdjListsGraphLoader::correctlyDefinedGraph(std::set<unsigned int> &vertices,
                                                std::set<Edge> &edges) {
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
