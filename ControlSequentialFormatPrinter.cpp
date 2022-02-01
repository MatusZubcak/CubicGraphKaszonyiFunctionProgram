//
// Created by Dell on 22. 11. 2021.
//

#include <fstream>
#include <iostream>
#include <map>
#include "ControlSequentialFormatPrinter.h"
#include "SequentialSuppressionNaive.h"
#include "SequentialSuppressionMemoized.h"


bool ControlSequentialFormatPrinter::print(CubicGraph &cubicGraph, const std::string &filename,
                                           append append) {
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
        std::vector<CubicGraph> suppressionSequence = SequentialSuppressionMemoized().findSuppressionSequence(cubicGraph);

        f << cubicGraph.size() << std::endl;
        for(auto it = suppressionSequence.begin(); it != suppressionSequence.end(); it++){
            printedSuccessfully &=
                    printIdAndDepth(*it, f)
                    && printGraph(*it, f)
                    && printKaszonyiValues(*it, f, IGNORE_EDGE_ORIGINALITY);
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

bool ControlSequentialFormatPrinter::print(std::vector<CubicGraph> &graphList, const std::string &filename,
                                           append append){
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
                            && printKaszonyiValues(*it, f, IGNORE_EDGE_ORIGINALITY);
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

