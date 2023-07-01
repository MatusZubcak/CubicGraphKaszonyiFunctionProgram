//
// Created by matus on 30.6.2023.
//

#include <fstream>
#include "GraphColoringsPrinter.h"



bool GraphColoringsPrinter::print(CubicGraph &cubicGraph, const std::string &filename,
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
            && printGraphColorings(cubicGraph, f);

    f.close();
    return printedSuccessfully;
}


bool GraphColoringsPrinter::print(std::vector<CubicGraph> &graphList, const std::string &filename,
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

        printedSuccessfully &=
        printGraph(*it, f)
        && printGraphColorings(*it, f);

        if (next(it) != graphList.end()) { f << std::endl; }
    }

    f.close();
    return printedSuccessfully;
}

bool GraphColoringsPrinter::print(CubicGraph &cubicGraph, const std::string &filename, append append) {
    return print(cubicGraph, filename, {}, append);
}

bool GraphColoringsPrinter::print(std::vector<CubicGraph> &graphList, const std::string &filename, append append) {
    return print(graphList, filename, {}, append);
}
