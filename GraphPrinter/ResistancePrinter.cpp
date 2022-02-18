//
// Created by Dell on 31. 1. 2022.
//

#include <iostream>
#include <fstream>
#include "ResistancePrinter.h"
#include "../Suppression/SequentialSuppressionMemoized.h"
#include "../Suppression/ParallelSuppressionMemoized.h"


bool ResistancePrinter::printResistanceValues(CubicGraph &cubicGraph, std::ofstream &f) {

    f << "SEQUENTIAL RESISTANCE: "
      << SequentialSuppressionMemoized().findSuppressionSequence(cubicGraph).back().getDepth()
      << std::endl;

    std::vector<CubicGraph> parallelSuppressionSequence =
            ParallelSuppressionMemoized().findSuppressionSequence(cubicGraph);

    if(parallelSuppressionSequence.back().isColorable()){
        f << "PARALLEL RESISTANCE: "
          << parallelSuppressionSequence.back().getDepth()
          << std::endl;
    } else{
        f << "PARALLEL RESISTANCE: "
          << "N/A"
          << std::endl;
    }


    return true;
}

bool ResistancePrinter::print(CubicGraph &cubicGraph, const std::string &filename,
                              const std::string &additionalInformation, append append) {

    bool printedSuccessfully;
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

        f << cubicGraph.size() << std::endl;
        printedSuccessfully =
                printGraph(cubicGraph, f)
                && printResistanceValues(cubicGraph, f);

        f.close();
    }catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }
    return printedSuccessfully;
}

bool ResistancePrinter::print(std::vector<CubicGraph> &graphList, const std::string &filename,
                              const std::string &additionalInformation, append append) {
    bool printedSuccesfully = true;
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

        f << graphList[0].size() << std::endl;
        for(auto it = graphList.begin(); it != graphList.end(); it++){
            printedSuccesfully &=
                    printResistanceValues(*it, f)
                    && printGraph(*it, f);
            if(next(it) != graphList.end()){f << std::endl;}
        }

        f.close();
    }catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }
    return printedSuccesfully;

}

bool ResistancePrinter::print(CubicGraph &cubicGraph, const std::string &filename, append append) {
    return print(cubicGraph, filename, "", append);
}

bool ResistancePrinter::print(std::vector<CubicGraph> &graphList, const std::string &filename, append append) {
    return print(graphList, filename, "", append);
}