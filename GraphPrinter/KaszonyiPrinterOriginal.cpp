//
// Created by matus on 8.9.2022.
//

#include "KaszonyiPrinterOriginal.h"
#include <iostream>
#include <fstream>


bool KaszonyiPrinterOriginal::print(CubicGraph &cubicGraph, const std::string &filename,
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

    if(cubicGraph.isColorable()){
        f << "3-EDGE-COLORABLE GRAPH" << std::endl;
        printedSuccessfully = printGraph(cubicGraph, f);

    }else {
        printedSuccessfully =
                printGraph(cubicGraph, f)
                && printKaszonyiValues(cubicGraph, f,
                                       IGNORE_EDGE_ORIGINALITY,
                                       COLORING_NUMBER_ORIGINAL);
    }

    f.close();
    return printedSuccessfully;
}


bool KaszonyiPrinterOriginal::print(std::vector<CubicGraph> &graphList, const std::string &filename,
                                      const std::vector<std::string> &additionalInformation,
                                      append append) {
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

    int i = 0;
    for(auto it = graphList.begin(); it != graphList.end(); it++){
        f << additionalInformation[i];
        i++;

       if(it->isColorable()){
           f << "3-EDGE-COLORABLE GRAPH" << std::endl;
           printedSuccessfully &= printGraph(*it, f);

       }else{
            printedSuccessfully &=
                    printGraph(*it, f)
                    && printKaszonyiValues(*it, f,
                                           IGNORE_EDGE_ORIGINALITY,
                                           COLORING_NUMBER_ORIGINAL);

        }
        if (next(it) != graphList.end()) { f << std::endl; }
    }

    f.close();
    return printedSuccessfully;

}

bool KaszonyiPrinterOriginal::print(CubicGraph &cubicGraph, const std::string &filename, append append) {
    return print(cubicGraph, filename, {}, append);
}

bool KaszonyiPrinterOriginal::print(std::vector<CubicGraph> &graphList, const std::string &filename, append append) {
    return print(graphList, filename, {}, append);
}
