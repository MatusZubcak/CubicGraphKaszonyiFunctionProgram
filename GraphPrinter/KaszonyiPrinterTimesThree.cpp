//
// Created by Dell on 2. 11. 2021.
//

#include <fstream>
#include <iostream>
#include <vector>
#include "KaszonyiPrinterTimesThree.h"


bool KaszonyiPrinterTimesThree::print(CubicGraph &cubicGraph, const std::string &filename,
                                      const std::vector<std::string> &additionalInformation,
                                      append append) {
    bool printedSuccessfully;
    std::ofstream f;
    if(append == APPEND) {
        f.open(filename, std::ios::app);
    }else {
        f.open(filename);
    }

    if(!f.good()) {
        throw FileCannotBeOpenedException();
    }
    f << additionalInformation.front();

    printedSuccessfully =
            printGraph(cubicGraph, f)
            && printKaszonyiValues(cubicGraph, f,
                                   IGNORE_EDGE_ORIGINALITY,
                                   COLORING_NUMBER_TIMES_THREE);

    f.close();

    return printedSuccessfully;
}

bool KaszonyiPrinterTimesThree::print(std::vector<CubicGraph> &graphList, const std::string &filename,
                                      const std::vector<std::string> &additionalInformation,
                                      append append) {
    bool printedSuccesfully = true;
    std::ofstream f;
    if(append == APPEND) {
        f.open(filename, std::ios::app);
    }else {
        f.open(filename);
    }


    if (!f) {
        throw FileCannotBeOpenedException();
    }

    int i = 0;
    for(auto it = graphList.begin(); it != graphList.end(); it++){
        f << additionalInformation[i];
        i++;

        printedSuccesfully &=
                printGraph(*it, f)
                && printKaszonyiValues(*it, f,
                                       IGNORE_EDGE_ORIGINALITY,
                                       COLORING_NUMBER_TIMES_THREE);
        if(next(it) != graphList.end()){f << std::endl;}
    }

    f.close();

    return printedSuccesfully;

}

bool KaszonyiPrinterTimesThree::print(CubicGraph &cubicGraph, const std::string &filename, append append) {
    return print(cubicGraph, filename, {}, append);
}

bool KaszonyiPrinterTimesThree::print(std::vector<CubicGraph> &graphList, const std::string &filename, append append) {
    return print(graphList, filename, {}, append);
}
