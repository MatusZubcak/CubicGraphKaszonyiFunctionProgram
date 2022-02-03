#include <chrono>
#include <iostream>
#include <fstream>
#include "Tests.h"
#include "GraphLoaderAdjLists.h"
#include "ControlSequentialFormatPrinter.h"
#include "ControlParallelFormatPrinter.h"
#include "KaszonyiValuesPrinter.h"
#include "ResistanceValuesPrinter.h"


void print(CubicGraph graph, const std::string& output, int& counter){

    for(auto e : graph.getEdges()){
        if(graph.getKaszonyiValue(e) != 0)
            return;
    }


    ControlSequentialFormatPrinter graphPrinterSequentialFormat = ControlSequentialFormatPrinter();
    ControlParallelFormatPrinter graphPrinterParallelFormat = ControlParallelFormatPrinter();
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
    graphPrinterParallelFormat.print(graph, parallel_output, NO_APPEND);
    graphPrinterSequentialFormat.print(graph, sequential_output, APPEND);

    std::cout << counter << std::endl;
    counter++;
}

/*
int main(){
    Tests::run();
    return 0;
}
*/


int main(){
    int repeats = 1;
    int size = 30;
    int file_index = 18;
    while(file_index <= 30) {
        std::cout << "GRAPH SIZE: " << file_index << std::endl;
        std::string filename = "s" + std::to_string(file_index) + "e3.txt";
        std::vector<CubicGraph> graphList = GraphLoaderAdjLists().loadNewGraphs(filename, SAT);
        //graphList.resize(size);
        auto t1 = std::chrono::high_resolution_clock::now();
        for (auto graph: graphList) {
            for (int i = 0; i < repeats; i++) {
                //graph.isColorable();
                for (auto e: graph.getEdges()) {
                    graph.suppressEdge(e).isColorable();
                }
            }
        }
        auto t2 = std::chrono::high_resolution_clock::now();

        auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

        std::chrono::duration<double, std::milli> ms_double = t2 - t1;

        std::cout << "SAT: ";
        std::cout << ms_int.count() << "ms\n";


        graphList = GraphLoaderAdjLists().loadNewGraphs(filename, FACTOR);
        //graphList.resize(size);
        t1 = std::chrono::high_resolution_clock::now();
        for (auto graph: graphList) {
            for (int i = 0; i < repeats; i++) {
                //graph.isColorable();
                for (auto e: graph.getEdges()) {
                    graph.suppressEdge(e).isColorable();
                }
            }
        }
        t2 = std::chrono::high_resolution_clock::now();

        ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

        ms_double = t2 - t1;

        std::cout << "Factor: ";
        std::cout << ms_int.count() << "ms\n";

        std::cout << "________________\n";
        file_index +=2;
    }
        return 0;
}


/*
int main(){
    GraphLoaderAdjLists graphLoaderAdjLists = GraphLoaderAdjLists();
    std::string input;
    std::cin >> input;

    while(input != "-1"){
        std::string output = input;
        output.erase(output.find(".txt"), 4);
        std::string output_single = output;
        std::string kas_output = output + "_KaszonyiValues.txt";
        std::string parallel_output = output + "_Parallel.txt";
        std::string sequential_output = output + "_Sequential.txt";
        std::string normal_output = output + "_Normal.txt";

        std::vector<CubicGraph> graphList = graphLoaderAdjLists.loadNewGraphs(input);

        KaszonyiValuesPrinter().print(graphList, kas_output, NO_APPEND);
        ControlParallelFormatPrinter().print(graphList, parallel_output, NO_APPEND);
        ControlSequentialFormatPrinter().print(graphList, sequential_output, NO_APPEND);
        ResistanceValuesPrinter().print(graphList,normal_output,NO_APPEND);

        std::cin >> input;
    }

    return 0;
}
*/

/*
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
*/


/*
int main(){
    std::remove("outS.txt");
    std::remove("outP.txt");
    std::string input;
    std::cin >> input;
    GraphLoaderAdjLists graphLoaderAdjLists;
    ControlSequentialFormatPrinter graphPrinterSequentialFormat;
    ControlParallelFormatPrinter graphPrinterParallelFormat;
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