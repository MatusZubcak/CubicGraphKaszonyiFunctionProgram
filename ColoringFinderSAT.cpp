//
// Created by Dell on 1. 2. 2022.
//

#include "ColoringFinderSAT.h"
#include "Hash.h"
#include <cryptominisat5/cryptominisat.h>
#include <unordered_map>

std::map<unsigned int, std::vector<unsigned int>>
ColoringFinderSAT::toIncidenceIndexMap(const std::set<unsigned int> &vertices, const std::set<Edge> &edges) {
    std::map<unsigned int, std::vector<unsigned int>> incidenceIndexMap;
    unsigned int index = 0;

    for(auto v : vertices){
        incidenceIndexMap[v] = std::vector<unsigned int>();
    }

    //Edge index multiplied by three because we use three color literals for every edge
    for(auto e : edges){
        //add incident edge index to vertex
        //multiple edge has more different indexes as it needs more literals
        std::pair<unsigned int, unsigned int> incVertices = e.getIncidentvertices();
        for(int i = 0; i < e.getMultiplicity(); i++){
            incidenceIndexMap[incVertices.first].push_back(3*(index + i));
            incidenceIndexMap[incVertices.second].push_back(3*(index + i));
        }
        index += e.getMultiplicity();
    }

    return incidenceIndexMap;
}

bool ColoringFinderSAT::isColorable(std::set<unsigned int> &vertices, std::set<Edge> &edges) {
    //map vertex -> List of indexes of incident edges
    std::map<unsigned int, std::vector<unsigned int>> incidenceIndexMap = toIncidenceIndexMap(vertices,edges);
    CMSat::SATSolver solver;

    //Let's use 1 thread
    solver.set_num_threads(1);

    //We need 3*|E(G)| = 9/2*|V(G)| variables.
    // Variable numbers are always trivially increasing
    solver.new_vars(9*vertices.size()/2);

    //Clauses for "At least one color for every edge"
    unsigned int e_index = 0;
    for(auto e : edges){
        for(int i = 0; i < e.getMultiplicity(); i++) {


            /*std::cout << " ("
                      << "x_" << e_index + 0 << " OR "
                      << "x_" << e_index + 1 << " OR "
                      << "x_" << e_index + 2
                      << ") ";
            std::cout << std::endl;*/


            std::vector<CMSat::Lit> clause = {
                    CMSat::Lit(e_index + 0, false),
                    CMSat::Lit(e_index + 1, false),
                    CMSat::Lit(e_index + 2, false)
            };
            solver.add_clause(clause);
            e_index += 3;
        }
    }

    //Clause at most one color of each type in edges incident with vertex v
    for(auto v : vertices){
        unsigned int e0_index = incidenceIndexMap[v][0];
        unsigned int e1_index = incidenceIndexMap[v][1];
        unsigned int e2_index = incidenceIndexMap[v][2];

        for(int i = 0; i < 3; i++){
            std::vector<CMSat::Lit> clause = {
                    CMSat::Lit(e0_index + i, true),
                    CMSat::Lit(e1_index + i, true)
            };
            solver.add_clause(clause);

            clause = {
                    CMSat::Lit(e0_index + i, true),
                    CMSat::Lit(e2_index + i, true)
            };
            solver.add_clause(clause);

            clause = {
                    CMSat::Lit(e1_index + i, true),
                    CMSat::Lit(e2_index + i, true)
            };
            solver.add_clause(clause);


            /*std::cout << " ("
                      << "NOT x_" << e0_index + i << " OR "
                      << "NOT x_" << e1_index + i
                      <<  ") ";

            std::cout << " ("
                      << "NOT x_" << e0_index + i << " OR "
                      << "NOT x_" << e2_index + i
                      <<  ") ";

            std::cout << " ("
                      << "NOT x_" << e1_index + i << " OR "
                      << "NOT x_" << e2_index + i
                      <<  ") ";

            std::cout << std::endl;
             */



        }
    }


    return solver.solve() == CMSat::l_True;
}

int ColoringFinderSAT::computeColorings(std::set<unsigned int> &vertices, std::set<Edge> &edges) {
    return 0;
}

int ColoringFinderSAT::computeColorings(std::set<unsigned int> &vertices, std::set<Edge> &edges,
                                        unsigned int numberOfIsolatedCircles) {
    return 0;
}

ColoringFinderSAT::ColoringFinderSAT() = default;
