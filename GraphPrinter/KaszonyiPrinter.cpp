//
// Created by Dell on 2. 11. 2021.
//

#include <fstream>
#include <iostream>
#include <vector>
#include "KaszonyiPrinter.h"


bool KaszonyiPrinter::print(CubicGraph &cubicGraph, const std::string &filename,
                            const std::string &additionalInformation,
                            append append) {
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
                && printKaszonyiValues(cubicGraph, f, IGNORE_EDGE_ORIGINALITY, COLORING_NUMBER);

        f.close();
    }catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f.close();
    }
    return printedSuccessfully;
}

bool KaszonyiPrinter::print(std::vector<CubicGraph> &graphList, const std::string &filename,
                            const std::string &additionalInformation,
                            append append) {
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
                    printGraph(*it, f)
                    && printKaszonyiValues(*it, f, IGNORE_EDGE_ORIGINALITY, COLORING_NUMBER);
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

bool KaszonyiPrinter::print(CubicGraph &cubicGraph, const std::string &filename, append append) {
    return print(cubicGraph, filename, "", append);
}

bool KaszonyiPrinter::print(std::vector<CubicGraph> &graphList, const std::string &filename, append append) {
    return print(graphList, filename, "", append);
}
