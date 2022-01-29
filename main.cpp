#include <iostream>
#include <fstream>
#include "Tests.h"
#include "GraphLoaderAdjLists.h"
#include "GraphPrinterSequentialFormat.h"
#include "GraphPrinterParallelFormat.h"
#include "GraphPrinterSemestralProjectFormat.h"

void print(CubicGraph graph, const std::string& output, int& counter){

    for(auto e : graph.getEdges()){
        if(graph.getKaszonyiValue(e) != 0)
            return;
    }


    GraphPrinterSequentialFormat graphPrinterSequentialFormat = GraphPrinterSequentialFormat();
    GraphPrinterParallelFormat graphPrinterParallelFormat = GraphPrinterParallelFormat();
    GraphPrinterSemestralProjectFormat graphPrinterSemestralProjectFormat = GraphPrinterSemestralProjectFormat();

    std::ofstream f;
    std::ofstream g;
    std::ofstream h;
    std::string parallel_output = output + "_parallel" + std::to_string(counter) + ".txt";
    std::string sequential_output = output + "_sequential.txt";
    std::string semestral_output = output + "_semestral.txt";

    f.open(parallel_output, std::ios::app);
    g.open(sequential_output, std::ios::app);
    h.open(semestral_output, std::ios::app);
    f << "____________________\n\n";
    g << "____________________\n\n";
    h << "___SEMESTRAL___\n\n";
    f.close();
    g.close();
    h.close();
    std::cout << counter << " BEFORE PARALLEL" << std::endl;
    graphPrinterParallelFormat.printKaszonyiValues(graph, parallel_output, NO_APPEND);
    graphPrinterSequentialFormat.printKaszonyiValues(graph, sequential_output, APPEND);
    graphPrinterSemestralProjectFormat.printKaszonyiValues(graph, semestral_output, APPEND);

    std::cout << counter << std::endl;
    counter++;
}
/*
int main(){
    Tests::run();
    return 0;
}
*/


int main() {
    GraphLoaderAdjLists graphLoaderAdjLists = GraphLoaderAdjLists();
    std::string input;
    std::cin >> input;
    int counter = 0;

    while(input != "-1"){
        counter = 0;
        std::string output = input;
        output.erase(output.find(".txt"), 4);

        std::ofstream f;
        //f.open(output + "_parallel.txt");
        //f.close();
        f.open(output + "_sequential.txt");
        f.close();
        f.open(output + "_semestral.txt");
        f.close();

        std::vector<CubicGraph> graphList = graphLoaderAdjLists.loadNewGraphs(input);
        for(const auto& graph : graphList) {
            print(graph, output, counter);
        }
        std::cin >> input;
    }

    //return Tests::run();
    return 0;
}


/*
int main(){
    std::remove("outS.txt");
    std::remove("outP.txt");
    std::string input;
    std::cin >> input;
    GraphLoaderAdjLists graphLoaderAdjLists;
    GraphPrinterSequentialFormat graphPrinterSequentialFormat;
    GraphPrinterParallelFormat graphPrinterParallelFormat;
    auto graphs = graphLoaderAdjLists.loadNewGraphs(input);
    while(!graphs.empty()) {
        auto g = graphs.front();
        graphs.pop();
        graphPrinterSequentialFormat.printKaszonyiValues(g, "outS.txt", APPEND);
        std::ofstream f;
        f.open("outS.txt", std::ios::app);
        f << std::endl;
        f.close();
    }

    graphs = graphLoaderAdjLists.loadNewGraphs(input);
    while(!graphs.empty()) {
        auto g = graphs.front();
        graphs.pop();
        graphPrinterParallelFormat.printKaszonyiValues(g, "outP.txt", APPEND);
        std::ofstream f;
        f.open("outP.txt", std::ios::app);
        f << std::endl;
        f.close();
    }

    return 0;
}*/