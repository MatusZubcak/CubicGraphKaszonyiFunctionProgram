#include <QApplication>
#include <QPushButton>

#include <chrono>
#include <iostream>
#include <fstream>
#include "Tests.h"
#include "GraphPrinter/SequentialPathPrinter.h"
#include "GraphPrinter/ParallelPathPrinter.h"
#include "GraphPrinter/KaszonyiPrinterTimesThree.h"
#include "GraphPrinter/KaszonyiPrinterOriginal.h"
#include "GraphPrinter/ResistancePrinter.h"
#include "ColoringFinder/SATColoringFinder.h"
#include "ColoringFinder/PDColoringFinder.h"
#include "Suppression/ParallelSuppressionMemoized.h"
#include "Suppression/SequentialSuppressionMemoized.h"
#include "Qt/QtMenuWindow.h"
#include "ColoringFinder/FactorColoringFinder.h"

// run graphical interface
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QtMenuWindow menuWindow;
    menuWindow.show();
    return QApplication::exec();
}

// run tests
/*
int main(){
    Tests::run();
    return 0;
}
*/