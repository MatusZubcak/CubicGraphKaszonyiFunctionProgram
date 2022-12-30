//
// Created by matus on 18.10.2022.
//

#include <algorithm>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <cmath>
#include <chrono>
#include "PDColoringFinder.h"
#include "../GraphExceptions.h"

boost::multiprecision::int1024_t
PDColoringFinder::computeColorings(std::set<unsigned int> &vertices, std::set<Edge> &edges,
                                   unsigned int numberOfIsolatedCircles) {

    bool hasLoop;
    setState(vertices, edges, hasLoop);
    if(hasLoop){
        return 0;
    }

    int graphHasPath = findPathDecomposition();
    std::cout << this->pathDepth << std::endl;

    colorings = coloringAlgorithm();
    //Take into account isolated circles
    colorings *= int(std::pow(double(3), double(numberOfIsolatedCircles)));
    //remove remaining permutations
    colorings /= 2;
    return colorings;
}

boost::multiprecision::int1024_t
PDColoringFinder::computeColorings(std::set<unsigned int> &vertices, std::set<Edge> &edges) {
    return computeColorings(vertices, edges, 0);
}


bool PDColoringFinder::isColorable(std::set<unsigned int> &vertices, std::set<Edge> &edges) {
    return computeColorings(vertices, edges, 0) != 0;
}

void PDColoringFinder::setState(std::set<unsigned int> &vertices, std::set<Edge> &edges, bool &containsLoop) {
    containsLoop = false;

    this->vertices = vertices;
    this->edges = edges;
    this->edgeOrdering = std::vector<Edge>();
    this->startingVertex = 0;
    this->pathDepth = 0;
    this->colorings = 0;

    unsigned int maxVertex = *(vertices.rbegin());
    this->adjLists = std::vector<std::vector<unsigned int>>(maxVertex + 1, std::vector<unsigned int>());

    for (Edge e: edges) {
        if (e.isLoop()) {
            containsLoop = true;
        }

        for (int i = 0; i < e.getMultiplicity(); i++) {
            auto v1 = e.getIncidentvertices().first;
            auto v2 = e.getIncidentvertices().second;
            adjLists[v1].push_back(v2);
            adjLists[v2].push_back(v1);
        }
    }

    this->components = {};
    bool allComponentsFound;
    std::unordered_map<unsigned int, bool> foundVertices;
    for (auto v: vertices) {
        foundVertices[v] = false;
    }
    do {

        unsigned int representant;
        for (auto [v, isFound]: foundVertices) {
            if (!isFound) {
                representant = v;
                break;
            }
        }
        std::vector<unsigned int> component = {representant};
        foundVertices[representant] = true;
        components.push_back(component);

        std::deque<unsigned int> queue;
        queue.push_back(representant);
        while (!queue.empty()) {
            auto v = queue.front();
            queue.pop_front();

            for (auto u: adjLists[v]) {
                if (!foundVertices[u]) {
                    foundVertices[u] = true;
                    queue.push_back(u);
                    components.back().push_back(u);
                }
            }
        }


        allComponentsFound = true;
        for (auto [v, isFound]: foundVertices) {
            allComponentsFound &= isFound;
        }
    } while (!allComponentsFound);

}

bool PDColoringFinder::addShortestHpath(std::unordered_set<unsigned int> &verticesInPathDecomposition,
                                        std::unordered_set<Edge, EdgeHash> &edgesInPathDecomposition,
                                        std::vector<Edge> &pathDecompositionEdgesOrdering,
                                        unsigned int &pathDecompositionDepth) {
    //initialize BFS queue
    std::unordered_map<unsigned int, unsigned int> vertexPredecessorMap;
    std::unordered_set<Edge, EdgeHash> traversedEdges;
    std::deque<Edge> hPath;
    bool hPathNotFound = true;

    std::deque<unsigned int> vertexVector;
    for(unsigned int v : verticesInPathDecomposition){
        vertexPredecessorMap[v] = v;
        vertexVector.push_back(v);
    }

    std::sort(vertexVector.begin(), vertexVector.end());

    std::queue<unsigned int, std::deque<unsigned int>> queue(std::deque<unsigned int>(vertexVector.begin(),
                                                                      vertexVector.end()));

    //find shortest H-path
    while(!queue.empty() && hPathNotFound){
        unsigned int v = queue.front();
        queue.pop();

        for(unsigned int neighbour : adjLists[v]){
            Edge e = Edge(v, neighbour);

            if( edgesInPathDecomposition.find(e) == edgesInPathDecomposition.end() &&
                traversedEdges.find(e) == traversedEdges.end()){
                traversedEdges.insert(e);

                if(vertexPredecessorMap.find(neighbour) == vertexPredecessorMap.end()){
                    vertexPredecessorMap[neighbour] = v;
                    queue.push(neighbour);
                }else{
                    // reconstruct H-path
                    bool hPathValid = true;
                    hPath.clear();
                    std::vector<bool> visitedVertices(adjLists.size(), false);
                    visitedVertices[v] = true;
                    visitedVertices[neighbour] = true;

                    hPath.emplace_front(v, neighbour);
                    unsigned int w = v;
                    while(vertexPredecessorMap[w] != w){
                        hPath.emplace_front(w, vertexPredecessorMap[w]);
                        w = vertexPredecessorMap[w];

                        if(visitedVertices[w] && verticesInPathDecomposition.find(w) == verticesInPathDecomposition.end()){
                            hPathValid = false;
                        }
                        visitedVertices[w] = true;
                    }

                    w = neighbour;
                    while(vertexPredecessorMap[w] != w){
                        hPath.emplace_back(w, vertexPredecessorMap[w]);
                        w = vertexPredecessorMap[w];

                        if(visitedVertices[w] && verticesInPathDecomposition.find(w) == verticesInPathDecomposition.end()){
                            hPathValid = false;
                        }
                        visitedVertices[w] = true;
                    }

                    //accept only if H-path is valid
                    if(hPathValid){
                        hPathNotFound = false;
                        break;
                    }
                }
            }
        }
    }

    if(hPathNotFound){
        return false;
    }

    // add new edges and vertices to containers
     for(Edge edge : hPath){

        pathDecompositionEdgesOrdering.push_back(*edges.find(edge));
        edgesInPathDecomposition.insert(edge);
        verticesInPathDecomposition.insert(edge.getIncidentvertices().first);
        verticesInPathDecomposition.insert(edge.getIncidentvertices().second);
    }

    unsigned int currentDepth = 0;
    for(unsigned int vertex : verticesInPathDecomposition){
        if(vertexInProgress(verticesInPathDecomposition, edgesInPathDecomposition, vertex)){
            currentDepth++;
        }
    }
    pathDecompositionDepth = std::max(pathDecompositionDepth, currentDepth);
    return true;
}


std::pair<unsigned int, std::vector<Edge>> PDColoringFinder::findPathForComponent(unsigned int componentId) {
    std::vector<Edge> bestEdgeOrdering = {};
    unsigned int bestDepth = 0;

    // probabilistic heuristic so we do not have to compute all possible paths
    auto& component = components[componentId];
    std::sort(component.begin(), component.end());
    std::srand(time(nullptr));
    unsigned int repeats = std::log2(component.size());

    for(int i = 0; i < 3*repeats; i++){
        unsigned int v;
        if(i < repeats){
            unsigned int index = std::pow(2, i) + (rand() % int(std::pow(2, i)));
            v = component[index % component.size()];
        }else{
        v = component[rand() % component.size()];
        }

        //check if edge is not multiplicity 3 -> then we want to handle it differently
        unsigned int neighbour = adjLists[v][0];
        Edge edge = Edge(v, neighbour);
        if(edges.find(edge) != edges.end()){
            Edge real_edge = *edges.find(edge);
            if(real_edge.getMultiplicity() == 3){
                bestDepth = 0;
                bestEdgeOrdering.push_back(real_edge);
                return {bestDepth, bestEdgeOrdering};
            }
        }else{
            throw PathDecompositionException();
        }

        // if edge has not multiplicity 3, we can compute component ordering the usual way
        std::unordered_set<unsigned int> verticesInPathDecomposition = {v};
        std::unordered_set<Edge, EdgeHash> edgesInPathDecomposition;
        std::vector<Edge> pathDecompositionEdgesOrdering;
        unsigned int pathDecompositionDepth = 0;

        //generates path decomposition starting in vertex v
        while (addShortestHpath(verticesInPathDecomposition,
                                edgesInPathDecomposition,
                                pathDecompositionEdgesOrdering,
                                pathDecompositionDepth)) {
        }

        //we can try if it is the best one (we will check if it is valid later on
        //path is invalid iff all paths are invalid)
        if (pathDecompositionDepth < bestDepth || bestDepth == 0) {
            bestDepth = pathDecompositionDepth;
            bestEdgeOrdering.clear();
            for (Edge e: pathDecompositionEdgesOrdering) {
                bestEdgeOrdering.push_back(e);
            }
        }
    }

    return {bestDepth, bestEdgeOrdering};
}

int PDColoringFinder::findPathDecomposition() {
    for(int i = 0; i < components.size(); i++) {
        std::pair<unsigned int, std::vector<Edge>> depth_edgeOrdering_pair = findPathForComponent(i);
        pathDepth += depth_edgeOrdering_pair.first;
        for(Edge e : depth_edgeOrdering_pair.second) {
            edgeOrdering.push_back(e);
        }
    }

    bool validDecomposition= true;
    std::unordered_map<Edge, bool, EdgeHash> edgeInDecompositionMap;
    for(Edge e : edges){
        edgeInDecompositionMap[e] = false;
    }

    for(Edge e : edgeOrdering){
        if(!edgeInDecompositionMap[e]){
            edgeInDecompositionMap[e] = true;
        }else{
            throw PathDecompositionException();
        }
    }
    for(auto item : edgeInDecompositionMap){
        validDecomposition &= item.second;
    }

    // if path decomposition is valid, we can set starting vertex
    // otherwise we know the graph is not colorable - it has bridge ---> we return -1 depth value
    if(validDecomposition) {

        if (edgeOrdering.size() >= 2 && edgeOrdering.front().getMultiplicity() != 3) {
            unsigned int v1 = edgeOrdering[1].getIncidentvertices().first;
            unsigned int v2 = edgeOrdering[1].getIncidentvertices().second;

            if (edgeOrdering.front().isIncidentWith(v1)) {
                startingVertex = edgeOrdering.front().getSecondVertex(v1);
            } else {
                startingVertex = edgeOrdering.front().getSecondVertex(v2);
            }
        } else {
            startingVertex = edgeOrdering.front().getIncidentvertices().first;
        }

        return int(pathDepth);
    }

    return -1;
}

bool PDColoringFinder::vertexInProgress(std::unordered_set<unsigned int> &verticesInPathDecomposition,
                                        std::unordered_set<Edge, EdgeHash> &edgesInPathDecomposition,
                                        unsigned int vertex) {
    if(verticesInPathDecomposition.find(vertex) == verticesInPathDecomposition.end()){
        return false;
    }

    int counter = 0;
    for(unsigned int neighbour : adjLists[vertex]){
        if(edgesInPathDecomposition.find(Edge(vertex, neighbour)) != edgesInPathDecomposition.end()){
            counter++;
        }
    }

    return(counter == 1 || counter == 2);
}

boost::multiprecision::int1024_t PDColoringFinder::coloringAlgorithm(){
    std::unordered_map< std::set<std::pair<unsigned int, unsigned int>>,
            boost::multiprecision::int1024_t, MapOfProcessedVerticesHash> dynamicMap;
    std::unordered_map<unsigned int, unsigned int> processedVertexDegreeMap;
    for(unsigned int v : this->vertices){
        processedVertexDegreeMap[v] = 0;
    }

    for(Edge e : edgeOrdering){
        unsigned int v1 = e.getIncidentvertices().first;
        unsigned int v2 = e.getIncidentvertices().second;
        unsigned int v1degree = processedVertexDegreeMap[v1];
        unsigned int v2degree = processedVertexDegreeMap[v2];
        if(v1degree > v2degree){
            std::swap(v1, v2);
            std::swap(v1degree, v2degree);
        }

        // Initialisation
        if(e == edgeOrdering.front()){

            std::set<std::pair<unsigned int, unsigned int>> edgeColor;
            switch (e.getMultiplicity()) {
                case 1:
                    edgeColor.insert(std::pair<unsigned int, unsigned int>(v1, 0));
                    edgeColor.insert(std::pair<unsigned int, unsigned int>(v2, 0));
                    dynamicMap[edgeColor] = 1;

                    processedVertexDegreeMap[v1] = 1;
                    processedVertexDegreeMap[v2] = 1;
                    break;
                case 2:
                    edgeColor.insert(std::pair<unsigned int, unsigned int>(v1, 2));
                    edgeColor.insert(std::pair<unsigned int, unsigned int>(v2, 2));
                    dynamicMap[edgeColor] = 2;

                    processedVertexDegreeMap[v1] = 2;
                    processedVertexDegreeMap[v2] = 2;
                    break;
                case 3:
                    dynamicMap[edgeColor] = 2;
                    processedVertexDegreeMap[v1] = 3;
                    processedVertexDegreeMap[v2] = 3;
                    break;
                default:
                    throw PathDecompositionException();
            }
        }else{
            // Dynamic programming step
            std::unordered_map< std::set<std::pair<unsigned int, unsigned int>>,
                    boost::multiprecision::int1024_t, MapOfProcessedVerticesHash> newDynamicMap;
            newDynamicMap.reserve(dynamicMap.size() * 10);

            //list of keys without v1, v2 vertices. We want to iterate through these later on
            std::vector<std::set<std::pair<unsigned int, unsigned int>>> filteredKeys;
            for(const auto& item : dynamicMap){
                if(item.second != 0) {
                    auto key = item.first;
                    for (int i = 0; i < 3; i++) {
                        key.erase(std::pair<unsigned int, unsigned int>(v1, i));
                        key.erase(std::pair<unsigned int, unsigned int>(v2, i));
                    }
                    filteredKeys.push_back(key);
                }
            }

            unsigned int edgeMultiplicityTwoVerticesDegree = 100*e.getMultiplicity() + 10*(v1degree) + v2degree;

            switch(edgeMultiplicityTwoVerticesDegree){
                case 100:
                    for(auto& key : filteredKeys){
                        for(int i = 0; i < 3; i ++){
                            auto newKey = key;
                            newKey.insert(std::pair<unsigned int, unsigned int>(v1, i));
                            newKey.insert(std::pair<unsigned int, unsigned int>(v2, i));
                            newDynamicMap[newKey] = dynamicMap[key];
                        }
                    }

                    dynamicMap = std::move(newDynamicMap);
                    break;

                case 101:
                    for(auto& key : filteredKeys){

                        for(int i = 0; i < 3; i ++){
                            for(int j = 0; j < 3; j++ ){
                                if(i != j){
                                    unsigned int z = (6 - (i + j)) % 3;
                                    auto newKey = key;
                                    newKey.insert(std::pair<unsigned int, unsigned int>(v1, i));
                                    newKey.insert(std::pair<unsigned int, unsigned int>(v2, j));

                                    auto tmpKey = key;
                                    tmpKey.insert((std::pair<unsigned int, unsigned int>(v2, z)));
                                    newDynamicMap[newKey] = dynamicMap[tmpKey];
                                }
                            }
                        }
                    }

                    dynamicMap = std::move(newDynamicMap);
                    break;

                case 102:
                    for(auto& key : filteredKeys){
                        for(int i = 0; i < 3; i ++){
                            auto newKey = key;
                            auto tmpKey = key;
                            newKey.insert(std::pair<unsigned int, unsigned int>(v1, i));
                            tmpKey.insert((std::pair<unsigned int, unsigned int>(v2, i)));
                            newDynamicMap[newKey] = dynamicMap[tmpKey];
                        }
                    }

                    dynamicMap = std::move(newDynamicMap);
                    break;

                case 111:
                    for(auto& key : filteredKeys){

                        for(int i = 0; i < 3; i ++){
                            for(int j = 0; j < 3; j++ ){
                                auto newKey = key;
                                newKey.insert(std::pair<unsigned int, unsigned int>(v1, i));
                                newKey.insert(std::pair<unsigned int, unsigned int>(v2, j));

                                if(i == j){
                                    unsigned int y = (i + 1)% 3;
                                    unsigned int z = (i + 2)% 3;

                                    auto tmpKey_Y = key;
                                    tmpKey_Y.insert(std::pair<unsigned int, unsigned int>(v1, y));
                                    tmpKey_Y.insert(std::pair<unsigned int, unsigned int>(v2, y));

                                    auto tmpKey_Z = key;
                                    tmpKey_Z.insert(std::pair<unsigned int, unsigned int>(v1, z));
                                    tmpKey_Z.insert(std::pair<unsigned int, unsigned int>(v2, z));
                                    newDynamicMap[newKey] = dynamicMap[tmpKey_Y] + dynamicMap[tmpKey_Z];
                                }else{
                                    auto tmpKey = key;
                                    tmpKey.insert(std::pair<unsigned int, unsigned int>(v1, j));
                                    tmpKey.insert(std::pair<unsigned int, unsigned int>(v2, i));

                                    newDynamicMap[newKey] = dynamicMap[tmpKey];
                                }
                            }
                        }
                    }

                    dynamicMap = std::move(newDynamicMap);
                    break;

                case 112:
                    for(auto& key : filteredKeys){
                        for(int i = 0; i < 3; i ++){
                            auto newKey = key;
                            newKey.insert(std::pair<unsigned int, unsigned int>(v1, i));

                            unsigned int y = (i + 1)% 3;
                            unsigned int z = (i + 2)% 3;

                            auto tmpKey_1 = key;
                            tmpKey_1.insert(std::pair<unsigned int, unsigned int>(v1, y));
                            tmpKey_1.insert(std::pair<unsigned int, unsigned int>(v2, z));

                            auto tmpKey_2 = key;
                            tmpKey_2.insert(std::pair<unsigned int, unsigned int>(v1, z));
                            tmpKey_2.insert(std::pair<unsigned int, unsigned int>(v2, y));
                            newDynamicMap[newKey] = dynamicMap[tmpKey_1] + dynamicMap[tmpKey_2];
                        }
                    }

                    dynamicMap = std::move(newDynamicMap);
                    break;

                case 122:
                    for(auto& key : filteredKeys){

                        auto newKey = key;
                        auto val = dynamicMap.begin()->second;
                        val = 0;
                        for(int i = 0; i < 3; i ++){
                            auto tmpKey = key;
                            tmpKey.insert((std::pair<unsigned int, unsigned int>(v1, i)));
                            tmpKey.insert((std::pair<unsigned int, unsigned int>(v2, i)));
                            val += dynamicMap[tmpKey];
                        }
                        newDynamicMap[newKey] = val;
                    }

                    dynamicMap = std::move(newDynamicMap);
                    break;

                case 200:
                    for(auto& key : filteredKeys){
                        for(int i = 0; i < 3; i ++){
                            auto newKey = key;
                            newKey.insert(std::pair<unsigned int, unsigned int>(v1, i));
                            newKey.insert(std::pair<unsigned int, unsigned int>(v2, i));
                            newDynamicMap[newKey] = 2 * dynamicMap[key];

                        }
                    }
                    dynamicMap = std::move(newDynamicMap);
                    break;
                case 201:
                    for(auto& key : filteredKeys){

                        for(int i = 0; i < 3; i ++){
                            auto newKey = key;
                            auto tmpKey = key;
                            newKey.insert(std::pair<unsigned int, unsigned int>(v1, i));
                            tmpKey.insert((std::pair<unsigned int, unsigned int>(v2, i)));
                            newDynamicMap[newKey] = 2 * dynamicMap[tmpKey];
                        }
                    }

                    dynamicMap = std::move(newDynamicMap);
                    break;
                case 211:
                    for(auto& key : filteredKeys){

                        auto newKey = key;
                        auto val = dynamicMap.begin()->second;
                        val = 0;
                        for(int i = 0; i < 3; i ++){
                            auto tmpKey = key;
                            tmpKey.insert((std::pair<unsigned int, unsigned int>(v1, i)));
                            tmpKey.insert((std::pair<unsigned int, unsigned int>(v2, i)));
                            val += dynamicMap[tmpKey];
                        }
                        newDynamicMap[newKey] = 2 * val;
                    }

                    dynamicMap = std::move(newDynamicMap);
                    break;
                case 300:
                    for(auto& key : filteredKeys){
                        newDynamicMap[key] = 6 * dynamicMap[key];
                    }

                    dynamicMap = std::move(newDynamicMap);
                    break;
                default:
                    throw PDColoringAlgorithmFailedException();
            }



            processedVertexDegreeMap[v1] += e.getMultiplicity();
            processedVertexDegreeMap[v2] += e.getMultiplicity();
        }
    }

    // Retrieve final value
    boost::multiprecision::int1024_t num_of_colorings = 0;
    for(const auto& item : dynamicMap){
        if(item.first.empty()){
            num_of_colorings += item.second;
        }
    }

    return num_of_colorings;
}

