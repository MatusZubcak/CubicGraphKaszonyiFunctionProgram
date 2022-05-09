//
// Created by Dell on 23. 11. 2021.
//

#include <fstream>
#include <iostream>
#include <map>
#include "ParallelPathPrinter.h"
#include "../Suppression/ParallelSuppressionNaive.h"
#include "../Suppression/ParallelSuppressionMemoized.h"


bool ParallelPathPrinter::print(CubicGraph &cubicGraph, const std::string &filename,
                                const std::string &additionalInformation, append append) {
    bool printedSuccessfully = true;
    std::ofstream f;
    if(append == APPEND)
        f.open(filename, std::ios::app);
    else
        f.open(filename);

    try{
        if (!f) {
            throw FileCannotBeOpenedException();
        }
        f << additionalInformation;

        std::vector<CubicGraph> suppressionSequence = ParallelSuppressionMemoized().findSuppressionSequence(cubicGraph);
        CubicGraph& lastGraph = suppressionSequence.back();

        f << cubicGraph.size() << std::endl;
        if(lastGraph.isColorable()) {
            f << "PARALLEL RESISTANCE: " << suppressionSequence.back().getDepth() << std::endl;
        }
        else{
            f << "PARALLEL RESISTANCE: " << "N/A" << std::endl;
        }

        for(auto it = suppressionSequence.begin(); it != suppressionSequence.end(); it++){
            printedSuccessfully &=
                    printIdAndDepth(*it, f)
                    && printGraph(*it, f)
                    && printKaszonyiValues(*it, f, MARK_ORIGINAL_EDGES, COLORING_EXISTS);
            if(next(it) != suppressionSequence.end()) {f << std::endl << std::endl;}
        }

        f.close();
    }catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }
    return printedSuccessfully;
}

bool ParallelPathPrinter::print(std::vector<CubicGraph> &graphList, const std::string &filename,
                                const std::string &additionalInformation, append append) {
    bool printedSuccessfully = true;
    std::ofstream f;
    if(append == APPEND)
        f.open(filename, std::ios::app);
    else
        f.open(filename);

    try{
        if (!f) {
            throw FileCannotBeOpenedException();
        }
        f << additionalInformation;

        for(const CubicGraph &cubicGraph : graphList) {
            std::vector<CubicGraph> suppressionSequence =
                    ParallelSuppressionMemoized().findSuppressionSequence(cubicGraph);
            CubicGraph& lastGraph = suppressionSequence.back();

            f << cubicGraph.size() << std::endl;
            if(lastGraph.isColorable()) {
                f << "PARALLEL RESISTANCE: " << suppressionSequence.back().getDepth() << std::endl;
            }
            else{
                f << "PARALLEL RESISTANCE: " << "N/A" << std::endl;
            }

            for (auto it = suppressionSequence.begin(); it != suppressionSequence.end(); it++) {

                printedSuccessfully &=
                        printIdAndDepth(*it, f)
                        && printGraph(*it, f)
                        && printKaszonyiValues(*it, f, MARK_ORIGINAL_EDGES, COLORING_EXISTS);
                if (next(it) != suppressionSequence.end()) { f << std::endl; }
            }

            if(&cubicGraph != &graphList.back()){
                f << std::endl
                  << "##############" << std::endl
                  << "# NEXT GRAPH #" << std::endl
                  << "##############" << std::endl
                  << std::endl;
            }

        }

        f.close();
    }catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }
    return printedSuccessfully;
}

bool ParallelPathPrinter::print(CubicGraph &cubicGraph, const std::string &filename, append append) {
    return print(cubicGraph, filename, "", append);
}

bool ParallelPathPrinter::print(std::vector<CubicGraph> &graphList, const std::string &filename, append append) {
    return print(graphList, filename, "", append);
}