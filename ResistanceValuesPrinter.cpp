//
// Created by Dell on 31. 1. 2022.
//

#include <iostream>
#include <fstream>
#include "ResistanceValuesPrinter.h"
#include "SequentialSuppressionMemoized.h"
#include "ParallelSuppressionMemoized.h"


bool ResistanceValuesPrinter::printResistanceValues(CubicGraph &cubicGraph, std::ofstream &f) {

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

bool ResistanceValuesPrinter::print(CubicGraph &cubicGraph, const std::string &filename, append append) {

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

bool ResistanceValuesPrinter::print(std::vector<CubicGraph> &graphList, const std::string &filename, append append) {
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
        f << graphList[0].size() << std::endl;
        for(auto it = graphList.begin(); it != graphList.end(); it++){
            printedSuccesfully &=
                    printGraph(*it, f)
                    && printResistanceValues(*it, f);
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
