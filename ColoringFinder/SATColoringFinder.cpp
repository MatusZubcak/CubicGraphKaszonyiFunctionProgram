//
// Created by Dell on 1. 2. 2022.
//

#include "SATColoringFinder.h"
#include "../Hash.h"
#include <unordered_map>
#include <cmath>


// generates incidence map: vertex -> list [incident edges]
// we need this map when we later add clauses "at most one color of each type in edges incident with vertex v"
std::map<unsigned int, std::vector<unsigned int>>
SATColoringFinder::toIncidenceIndexMap(const std::set<unsigned int> &vertices, const std::set<Edge> &edges) {
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

// converts cubic graph 3-edge-coloring problem to SAT problem
void SATColoringFinder::toSATFormula(const std::set<unsigned int> &vertices, const std::set<Edge> &edges,
                                     CMSat::SATSolver &satSolver) {
    //map: vertex -> list[incident edges]
    std::map<unsigned int, std::vector<unsigned int>> incidenceIndexMap = toIncidenceIndexMap(vertices,edges);

    //Clauses "At least one color for every edge"
    unsigned int e_index = 0;
    for(auto e : edges){
        for(int i = 0; i < e.getMultiplicity(); i++) {

            std::vector<CMSat::Lit> clause = {
                    CMSat::Lit(e_index + 0, false),
                    CMSat::Lit(e_index + 1, false),
                    CMSat::Lit(e_index + 2, false)
                    };
            satSolver.add_clause(clause);
            e_index += 3;
        }
    }

    //Clause "At most one color of each type in edges incident with vertex v"
    for(auto v : vertices){
        unsigned int e0_index = incidenceIndexMap[v][0];
        unsigned int e1_index = incidenceIndexMap[v][1];
        unsigned int e2_index = incidenceIndexMap[v][2];

        for(int i = 0; i < 3; i++){
            std::vector<CMSat::Lit> clause = {
                    CMSat::Lit(e0_index + i, true),
                    CMSat::Lit(e1_index + i, true)
                    };
            satSolver.add_clause(clause);

            clause = {
                    CMSat::Lit(e0_index + i, true),
                    CMSat::Lit(e2_index + i, true)
                    };
            satSolver.add_clause(clause);

            clause = {
                    CMSat::Lit(e1_index + i, true),
                    CMSat::Lit(e2_index + i, true)
                    };
            satSolver.add_clause(clause);
        }
    }
}

//computes all 3-edge-colorings for given graph
int SATColoringFinder::computeColorings(std::set<unsigned int> &vertices, std::set<Edge> &edges,
                                        unsigned int numberOfIsolatedCircles) {
    CMSat::SATSolver satSolver;
    int colorings = 0;

    //Let's use 1 thread
    // We have experimentally found this was fastest for some reason
    satSolver.set_num_threads(1);

    //We need 3*|E(G)| = 9/2*|V(G)| variables.
    // Variable numbers are always trivially increasing
    satSolver.new_vars(9*vertices.size()/2);

    //generate SAT formula of edge 3-coloring problem
    toSATFormula(vertices, edges, satSolver);

    while(true) {
        //If no more solutions exist, return all found colorings
        if ( satSolver.solve() != CMSat::l_True) {
            //Do not include permutations of colors
            colorings = colorings / 6;

            //Take isolated circles into account
            colorings *= int(std::pow(double(3), double(numberOfIsolatedCircles)));

            return colorings;
        }

        //Banning found solution
        std::vector<CMSat::Lit> ban_solution;
        for (auto var = 0; var < satSolver.nVars(); var++) {
            if (satSolver.get_model()[var] != CMSat::l_Undef) {
                ban_solution.emplace_back(var, (satSolver.get_model()[var] == CMSat::l_True));
            }
        }
        satSolver.add_clause(ban_solution);

        //Increase amount of colorings
        colorings++;
    }
}

int SATColoringFinder::computeColorings(std::set<unsigned int> &vertices, std::set<Edge> &edges) {
    return computeColorings(vertices, edges, 0);
}

// Finds out whether graph is 3-edge-colorable
bool SATColoringFinder::isColorable(std::set<unsigned int> &vertices, std::set<Edge> &edges) {
    CMSat::SATSolver satSolver;

    //Let's use 1 thread
    // We have experimentally found this was fastest for some reason
    satSolver.set_num_threads(1);

    //We need 3*|E(G)| = 9/2*|V(G)| variables.
    // Variable numbers are always trivially increasing
    satSolver.new_vars(9*vertices.size()/2);

    //generate SAT formula of edge 3-coloring problem
    toSATFormula(vertices, edges, satSolver);

    return satSolver.solve() == CMSat::l_True;
}