//
// Created by Dell on 22. 11. 2021.
//

#include <fstream>
#include <iostream>
#include <map>
#include "SequentialPathPrinter.h"
#include "../Suppression/SequentialSuppressionNaive.h"
#include "../Suppression/SequentialSuppressionMemoized.h"


bool SequentialPathPrinter::print(CubicGraph &cubicGraph, const std::string &filename,
                                  const std::string &additionalInformation, append append) {
    bool printedSuccessfully = true;
    std::ofstream f;
    if(append == APPEND) {
        f.open(filename, std::ios::app);
    }else {
        f.open(filename);
    }

    if (!f) {
        throw FileCannotBeOpenedException();
    }
    f << additionalInformation;

    std::vector<CubicGraph> suppressionSequence = SequentialSuppressionMemoized().findSuppressionSequence(cubicGraph);

    f << cubicGraph.size() << std::endl;
    for(auto it = suppressionSequence.begin(); it != suppressionSequence.end(); it++){
        printedSuccessfully &=
                printIdAndDepth(*it, f)
                && printGraph(*it, f)
                && printKaszonyiValues(*it, f, IGNORE_EDGE_ORIGINALITY, COLORING_EXISTS);
        if(next(it) != suppressionSequence.end()) {f << std::endl << std::endl;}
    }

    f.close();

    return printedSuccessfully;
}

bool SequentialPathPrinter::print(std::vector<CubicGraph> &graphList, const std::string &filename,
                                  const std::string &additionalInformation, append append){
        bool printedSuccessfully = true;
        std::ofstream f;
        if(append == APPEND)
            f.open(filename, std::ios::app);
        else
            f.open(filename);


    if (!f) {
        throw FileCannotBeOpenedException();
    }
    f << additionalInformation;

    for(const CubicGraph& cubicGraph : graphList) {

        std::vector<CubicGraph> suppressionSequence = SequentialSuppressionMemoized().findSuppressionSequence(
                cubicGraph);
        CubicGraph& lastGraph = suppressionSequence.back();

        f << cubicGraph.size() << std::endl;
        if(lastGraph.isColorable()) {
            f << "SEQUENTIAL RESISTANCE: " << suppressionSequence.back().getDepth() << std::endl;
        }
        else{
            f << "SEQUENTIAL RESISTANCE: " << "N/A" << std::endl;
        }

        for (auto it = suppressionSequence.begin(); it != suppressionSequence.end(); it++) {
            printedSuccessfully &=
                    printIdAndDepth(*it, f)
                    && printGraph(*it, f)
                    && printKaszonyiValues(*it, f, IGNORE_EDGE_ORIGINALITY, COLORING_EXISTS);
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
        return printedSuccessfully;
    }

bool SequentialPathPrinter::print(CubicGraph &cubicGraph, const std::string &filename, append append) {
    return print(cubicGraph, filename, "", append);
}

bool SequentialPathPrinter::print(std::vector<CubicGraph> &graphList, const std::string &filename, append append) {
    return print(graphList, filename, "", append);
}