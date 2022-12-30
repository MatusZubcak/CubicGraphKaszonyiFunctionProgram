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
                                  const std::vector<std::string> &additionalInformation, append append) {
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
    f << additionalInformation.front();

    std::vector<CubicGraph> suppressionSequence = SequentialSuppressionMemoized().findSuppressionSequence(cubicGraph);

    for(auto it = suppressionSequence.begin(); it != suppressionSequence.end(); it++){
        printedSuccessfully &=
                printIdAndDepth(*it, f)
                && printGraph(*it, f);
                //&& printKaszonyiValues(*it, f, IGNORE_EDGE_ORIGINALITY, COLORING_EXISTS);
        if(next(it) != suppressionSequence.end()) {f << std::endl << std::endl;}
    }

    f.close();

    return printedSuccessfully;
}

bool SequentialPathPrinter::print(std::vector<CubicGraph> &graphList, const std::string &filename,
                                  const std::vector<std::string> &additionalInformation, append append){
        bool printedSuccessfully = true;
        std::ofstream f;
        if(append == APPEND)
            f.open(filename, std::ios::app);
        else
            f.open(filename);


    if (!f) {
        throw FileCannotBeOpenedException();
    }

    int i = 0;
    for(const CubicGraph& cubicGraph : graphList) {
        f << additionalInformation[i];
        i++;

        std::vector<CubicGraph> suppressionSequence = SequentialSuppressionMemoized().findSuppressionSequence(
                cubicGraph);
        CubicGraph& lastGraph = suppressionSequence.back();

        if(lastGraph.isColorable()) {
            f << "SERIAL RESISTANCE: " << suppressionSequence.back().getDepth() << std::endl;
        }
        else{
            f << "SERIAL RESISTANCE: " << "N/A" << std::endl;
        }

        for (auto it = suppressionSequence.begin(); it != suppressionSequence.end(); it++) {
            printedSuccessfully &=
                    printIdAndDepth(*it, f)
                    && printGraph(*it, f);
                    //&& printKaszonyiValues(*it, f, IGNORE_EDGE_ORIGINALITY, COLORING_EXISTS);
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
    return print(cubicGraph, filename, {}, append);
}

bool SequentialPathPrinter::print(std::vector<CubicGraph> &graphList, const std::string &filename, append append) {
    return print(graphList, filename, {}, append);
}