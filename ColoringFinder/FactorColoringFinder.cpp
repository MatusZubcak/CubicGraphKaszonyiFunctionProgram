//
// Created by Matus on 25. 10. 2021.
//

#include <iostream>
#include <cmath>
#include "FactorColoringFinder.h"

// 3-edge-coloring finder based on equivalence of the 3-edge-coloring and
// a 1-factor and a set of cykles with even length
FactorColoringFinder::FactorColoringFinder(){
    colorings = 0;
};

//convert graph format from set of vertices and edges to adjacency lists stored in single array
std::vector<std::pair<unsigned int,bool>>FactorColoringFinder::convertToLinearGraphRepresentation
            (std::set<unsigned int>& vertices, std::set<Edge>& edges){
    std::unordered_map<unsigned int, unsigned int> vertexTranslationTable;
    unsigned int indexGenerator = 0;
    for(auto v : vertices){
        vertexTranslationTable[v] = indexGenerator;
        indexGenerator++;
    }

    std::vector<std::pair<unsigned int, bool>>linearGraphRepresentation
            (3*vertexTranslationTable.size(), std::pair<int,bool>(0, true));

    for(auto e : edges){
        unsigned int v1 = vertexTranslationTable[e.getIncidentvertices().first];
        unsigned int v2 = vertexTranslationTable[e.getIncidentvertices().second];
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

// find whether cycle is even length
// if so, removes it from the graph representation as we do not want to compute the same cycle twice
// otherwise returns information that this is not proper 3-edge-coloring
bool FactorColoringFinder::cycleIsEven
            (std::vector< std::pair<unsigned int, bool>> &linearGraphRepresentation,
             unsigned int vertex){

    int verticesInCycle = 0;
    unsigned int current = vertex;
    do{
        int next;
        for(int i = 0; i < 3; i++){
            if(!linearGraphRepresentation[3 * current + i].second){
                next = linearGraphRepresentation[ 3*current + i].first;
            }
            linearGraphRepresentation[ 3*current + i].second = true;
        }

        bool edgeAdded = false;
        for(int i = 0; i < 3; i++){
            if(!edgeAdded && !linearGraphRepresentation[ 3*next + i].second &&linearGraphRepresentation[ 3*next + i].first == current) {
                linearGraphRepresentation[3 * next + i].second = true;
                edgeAdded = true;
            }
        }

        current = next;
        verticesInCycle++;
    }while(current != vertex);

    if( verticesInCycle%2 == 0) return true;
    return false;
}

// recursively (using backtrack algorithm) generates all 1-factors and for each of them
// computes the amount of proper 3-edge-colorings
void FactorColoringFinder::recursivelyCountKaszonyi
            (std::vector<std::pair<unsigned int, bool>> linearGraphRepresentation,
             unsigned int vertex){

    // if every vertex is covered by 1-factor, then look at the set of cycles (are they all even?)
    if(3*vertex >= linearGraphRepresentation.size()){

        int potentialPsiForThis1Factor = 1;
        int lGR_size = linearGraphRepresentation.size();
        for(int i = 0; i < lGR_size; i++){
            if(!linearGraphRepresentation[i].second){
                if(cycleIsEven(linearGraphRepresentation, i/3)){
                    potentialPsiForThis1Factor = 2*potentialPsiForThis1Factor;
                } else{
                    return;
                }
            }
        }

        // we divide colorings by two because in reality we ignore colorings that
        // can obtained by permutation of colors from some different coloring
        colorings += potentialPsiForThis1Factor/2;
        return;
    }

    // if vertex already has edge, we do not want to add another incident edge to 1-factor
    if(linearGraphRepresentation[ 3*vertex ].second ||
       linearGraphRepresentation[ 3*vertex + 1 ].second ||
       linearGraphRepresentation[ 3*vertex + 2 ].second){
        recursivelyCountKaszonyi(linearGraphRepresentation, vertex+1);
        return;
    }
    else{ // if vertex is not covered by 1-factor, try adding incident edge to 1-factor
        bool edgeAdded = false;
        for(int i = 0; i < 3; i++){
            if(linearGraphRepresentation[ 3*vertex + i].first > vertex){
                int neighbour = linearGraphRepresentation[ 3*vertex + i].first;
                bool neighbourHasEdge = false;
                for(int j = 0; j < 3; j++){
                    if(linearGraphRepresentation[ 3*neighbour + j].second) neighbourHasEdge = true;
                }

                if(!neighbourHasEdge){
                    linearGraphRepresentation[ 3*vertex + i].second = true;
                    int neighbourAddedEdge = -1;
                    for(int j = 0; j < 3; j++){
                        if(neighbourAddedEdge == -1 && linearGraphRepresentation[ 3*neighbour + j].first == vertex){
                            neighbourAddedEdge = 3*neighbour + j;
                            linearGraphRepresentation[ 3*neighbour + j].second = true;
                        }
                    }

                    edgeAdded = true;
                    recursivelyCountKaszonyi(linearGraphRepresentation, vertex+1);
                    linearGraphRepresentation[neighbourAddedEdge].second = false;
                    linearGraphRepresentation[ 3*vertex + i].second = false;
                }

            }
        }
        // if none of edges incident with given vertex can be added to 1-factor,
        // then it is not proper 1-factor and we want to stop computing this branch
        if(!edgeAdded) return;
    }


}

// computes all 3-edge-colorings for given graph
// first, using "convertToLinearGraphRepresentation" function it converts graph to wanted format
// then using "recursivelyCountKaszonyi" we compute the number of all 3-edge-colorings
unsigned long long FactorColoringFinder::computeColorings(std::set<unsigned int>& vertices,
                                           std::set<Edge>& edges,
                                           unsigned int numberOfIsolatedCircles) {

    colorings = 0;
    std::vector<std::pair<unsigned int, bool>> linearGraphRepresentation =
            convertToLinearGraphRepresentation(vertices, edges);

    if(!linearGraphRepresentation.empty()) {
        // one edge will be in all 1-factors, so we do not generate 3-edge-colorings, that can be
        // obtained from another 3-edge-coloring with permutation of colors
        // also speeds things up a bit
        linearGraphRepresentation[0].second = true;
        unsigned int neighbour = linearGraphRepresentation[0].first;
        for (int j = 0; j < 3; j++) {
            if (linearGraphRepresentation[3 * neighbour + j].first == 0) {
                linearGraphRepresentation[3 * neighbour + j].second = true;
                break;
            }
        }
        //for remaining edges we generate all 1-factors using backtracking
        recursivelyCountKaszonyi(linearGraphRepresentation, 1);
    } else{
        colorings = 1;
    }

    colorings *= int(std::pow(double(3), double(numberOfIsolatedCircles)));
    return colorings;
}

unsigned long long FactorColoringFinder::computeColorings(std::set<unsigned int> &vertices, std::set<Edge> &edges){
    return computeColorings(vertices, edges, 0);
}

// finds if graph is 3-edge-colorable by computing all colorings and comparing result with 0
bool FactorColoringFinder::isColorable(std::set<unsigned int> &vertices, std::set<Edge> &edges) {
    return computeColorings(vertices, edges, 0) > 0;
}