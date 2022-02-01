//
// Created by Dell on 25. 10. 2021.
//

#include <iostream>
#include <cmath>
#include "KaszonyiFactorFunction.h"

std::vector<std::pair<unsigned int,bool>>KaszonyiFactorFunction::convertToLinearGraphRepresentation
            (std::set<unsigned int>& vertices, std::set<Edge>& edges){
    std::unordered_map<unsigned int, unsigned int> vertexTranslationTable;
    unsigned int indexGenerator = 0;
    for(auto v : vertices){
        vertexTranslationTable[v] = indexGenerator;
        indexGenerator++;
    }

    /*for(auto e : vertexTranslationTable){
        std::cout << "key: " << e.first << " value: " << e.second <<std::endl;
    }*/

    std::vector<std::pair<unsigned int, bool>>linearGraphRepresentation
            (3*vertexTranslationTable.size(), std::pair<int,bool>(0, true));

    /*for(auto i : linearGraphRepresentation){
        std::cout << i.first << "   ";
    } std::cout << std::endl;
    for(auto e : edges){
        std::cout << e.toString() << "  ";
    }std::cout <<std::endl;*/

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
       /*std::cout << "VERTICES: " << v1 << " " << v2 << std::endl;
        for(auto i : linearGraphRepresentation){
            std::cout << i.first << "  ";
        }std::cout << std::endl;
        for(auto i : linearGraphRepresentation){
            std::cout << i.second <<"  ";
        } std::cout << "\n";*/
    }

    /*for(auto i : linearGraphRepresentation){
        std::cout << i.second <<"   ";
    } std::cout << "BOOLS\n";
    for(auto i : linearGraphRepresentation){
        std::cout << i.first << " ";
    }std::cout <<std::endl;*/
    return linearGraphRepresentation;
}

KaszonyiFactorFunction::KaszonyiFactorFunction(){
    kaszonyiValue = 0;
};

/*zisti ci je kruznica parnej dlzky.
 * Ak je, vykona aj reziu potrebnu na "vymazanie" danych hran z grafovej reprezentacie
 * aby sme tu istu kruznicu nepocitali 2-krat*/
bool KaszonyiFactorFunction::cycleIsEven
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


/* rekurzivne zgeneruje vsetky mozne 1-faktory a vypocita pre kazdy z nich pocet ofarbeni */
void KaszonyiFactorFunction::reccursivellyCountKaszonyi
            (std::vector<std::pair<unsigned int, bool>> &linearGraphRepresentation,
             unsigned int vertex){
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
        //delime dvomi, lebo v skutocnosti tymto sposobom generujeme nie kombinacie ale permutacie rozdelenia 2-faktoru do 2 farieb
        kaszonyiValue += potentialPsiForThis1Factor/2;
        return;
    }

    //ak uz ma hranu tento vrchol, nema zmysel mu ju pridavat, rovno ideme na dalsi vrchol
    if(linearGraphRepresentation[ 3*vertex ].second ||
       linearGraphRepresentation[ 3*vertex + 1 ].second ||
       linearGraphRepresentation[ 3*vertex + 2 ].second){
        reccursivellyCountKaszonyi(linearGraphRepresentation, vertex+1);
        return;
    }
    else{ //ak nema hranu, pokusime sa mu ju pridat
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
                    reccursivellyCountKaszonyi(linearGraphRepresentation, vertex+1);
                    linearGraphRepresentation[neighbourAddedEdge].second = false;
                    linearGraphRepresentation[ 3*vertex + i].second = false;
                }

            }
        }
        //ak sa nepodarilo hranu pridat, nema zmysel dalej uvazovat rekurziu
        if(!edgeAdded) return;
    }


}

int KaszonyiFactorFunction::getKaszonyiValue(std::set<unsigned int>& vertices,
                                             std::set<Edge>& edges,
                                             unsigned int numberOfIsolatedCircles) {

    kaszonyiValue = 0;
    std::vector<std::pair<unsigned int, bool>> linearGraphRepresentation =
            convertToLinearGraphRepresentation(vertices, edges);

    if(!linearGraphRepresentation.empty()) {
        //fixne nastavime jednu pevnu hranu v 1-faktore, aby sme negenerovali moznosti navyse
        linearGraphRepresentation[0].second = true;
        unsigned int neighbour = linearGraphRepresentation[0].first;
        for (int j = 0; j < 3; j++) {
            if (linearGraphRepresentation[3 * neighbour + j].first == 0) {
                linearGraphRepresentation[3 * neighbour + j].second = true;
                break;
            }
        }
        //pre zvysne volame rekurzivnu funkciu na hladanie 1-faktoru
        reccursivellyCountKaszonyi(linearGraphRepresentation, 1);
    } else{
        kaszonyiValue = 1;
    }

    kaszonyiValue *= int(std::pow(double(3), double(numberOfIsolatedCircles)));
    return kaszonyiValue;
}

int KaszonyiFactorFunction::getKaszonyiValue(std::set<unsigned int> &vertices, std::set<Edge> &edges){
    return getKaszonyiValue(vertices, edges, 0);
}
