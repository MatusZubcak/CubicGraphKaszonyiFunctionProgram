//
// Created by matus on 8.9.2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_KASZONYIPRINTERORIGINAL_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_KASZONYIPRINTERORIGINAL_H


#include "GraphPrinter.h"

class KaszonyiPrinterOriginal : public GraphPrinter {
public:
    KaszonyiPrinterOriginal()=default;;

    bool print(CubicGraph& cubicGraph, const std::string& filename, append append) override;
    bool print(std::vector<CubicGraph>& graphList, const std::string& filename, append append) override;
    bool print(CubicGraph &cubicGraph, const std::string &filename, const std::vector<std::string>& additionalInformation,
               append append) override;
    bool print(std::vector<CubicGraph> &graphList, const std::string &filename,
               const std::vector<std::string>& additionalInformation, append append) override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_KASZONYIPRINTERORIGINAL_H
