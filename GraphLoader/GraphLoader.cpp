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

// loads graphs in formats described in program instructions
std::vector<CubicGraph> GraphLoader::loadNewGraphs(const std::string& filename,
                                                   std::vector<std::string>& informationFromFile,
                                                   coloringAlgorithm coloringAlgorithm) {
    informationFromFile = {};
    std::vector<CubicGraph> graphList = {};
    std::ifstream f;
    f.open(filename);
    std::string infoString;
    std::string buffer, word, prev_buffer;
    unsigned int firstGraphSize = 0;

    if (!f.good()) {
        throw FileCannotBeOpenedException();
    }

    while(std::getline(f, buffer)) {
        bool addStringStreamToInfoString = true;
        std::stringstream stringStream(buffer);

        std::vector<std::string> stringList;
        while (stringStream >> word) {
            stringList.push_back(word);
        }

        if (stringList.size() == 3) {

            std::vector<unsigned int> firstAdjList;
            bool all_are_vertex_numbers = true;

            for(auto s : stringList){
                if(!(std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end())){
                    all_are_vertex_numbers = false;
                }else{
                    firstAdjList.push_back(std::stoul(s));
                }
            }

            if(all_are_vertex_numbers){
                informationFromFile.push_back(infoString);
                infoString = "";
                addStringStreamToInfoString = false;

                unsigned int currentGraphSize;
                if(!prev_buffer.empty()){
                    currentGraphSize = std::stoul(prev_buffer);
                    if(firstGraphSize == 0){
                        firstGraphSize = currentGraphSize;
                    }
                }else{
                    currentGraphSize = firstGraphSize;
                }

                loadGraph(graphList, f, currentGraphSize, coloringAlgorithm, firstAdjList);
            }
        }

        if(addStringStreamToInfoString && !stringStream.str().empty()) {
            infoString += stringStream.str() + "\n";
        }

        if(stringList.empty()){
            prev_buffer = "";
        }else{
            prev_buffer = stringList.front();
        }
    }

    f.close();

    if(graphList.size() != informationFromFile.size()){
        throw BadFileInfoSizeException();
    }

    return graphList;
}

std::vector<CubicGraph> GraphLoader::loadNewGraphs(const std::string &filename,
                                                   std::vector<std::string>& informationFromFile) {
    return loadNewGraphs(filename, informationFromFile, ANY);
}

std::vector<CubicGraph> GraphLoader::loadNewGraphs(const std::string &filename,
                                                           coloringAlgorithm coloringAlgorithm) {
    std::vector<std::string> dump_string;
    return loadNewGraphs(filename, dump_string, coloringAlgorithm);
}

std::vector<CubicGraph> GraphLoader::loadNewGraphs(const std::string &filename) {
    std::vector<std::string> dump_string;
    return loadNewGraphs(filename, dump_string, ANY);
}



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

    if(std::getline(f, buffer)) {
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
        return true;
    }else

    return false;
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
void GraphLoader::loadGraph(std::vector<CubicGraph> &graphList, std::ifstream &f, unsigned int graph_size,
                            coloringAlgorithm coloringAlgorithm, const std::vector<unsigned int>& firstAdjList) {
    unsigned int neighbour1 = firstAdjList[0],
                 neighbour2 = firstAdjList[1],
                 neighbour3 = firstAdjList[2];
    bool firstRun = true;

    std::set<unsigned int> vertices;
    std::set<Edge> edges;
    for (int i = 0; i < graph_size; i++) {
        vertices.insert(vertices.end(), i);
    }

    for (int currentVertex = 0; currentVertex < graph_size; currentVertex++) {
        //we want to add first vertices from firstAdjList not from fstream file
        if(firstRun){
            firstRun = false;
        //otherwise we can load new triple of neighbours from the file
        }else{
            if(!loadNeighbours(f, neighbour1, neighbour2, neighbour3)){
                //Not enough vertices to load full graph
                throw BadFileException();
            }
        }
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

    } else{
        throw BadlyDefinedGraphException();
    }
}