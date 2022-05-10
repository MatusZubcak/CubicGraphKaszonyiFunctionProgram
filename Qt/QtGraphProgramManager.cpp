//
// Created by matus on 9.5.2022.
//

#include <iostream>
#include <QMessageBox>
#include "QtGraphProgramManager.h"
#include "../GraphLoader/AdjListsGraphLoader.h"
#include "../GraphPrinter/ResistancePrinter.h"
#include "../GraphPrinter/ParallelPathPrinter.h"
#include "../GraphPrinter/SequentialPathPrinter.h"
#include "../GraphPrinter/KaszonyiPrinter.h"

void
QtGraphProgramManager::runGraphProgram(formatType formatType, QStringList filePaths, QString outputDirectory) {
    AdjListsGraphLoader adjListsGraphLoader = AdjListsGraphLoader();
    std::string informationFromFile;
    std::vector<CubicGraph> graphList;


    for(QString &filePath : filePaths){
        QString fileName = filePath.section('/', -1);
            std::string outputFilePath = outputDirectory.toStdString() + "/" + fileName.toStdString() + ".out";
            try{
                graphList = adjListsGraphLoader.loadNewGraphs(filePath.toStdString(), informationFromFile);

                switch(formatType){
                    case RESISTANCE_VALUES:
                        ResistancePrinter().print(graphList,outputFilePath,informationFromFile,
                                                  NO_APPEND);
                        break;
                    case PARALLEL_PATH:
                        ParallelPathPrinter().print(graphList,outputFilePath,informationFromFile,
                                                    NO_APPEND);
                        break;
                    case SEQUENTIAL_PATH:
                        SequentialPathPrinter().print(graphList,outputFilePath,informationFromFile,
                                                      NO_APPEND);
                        break;
                    case KASZONYI_FUNCTION:
                        KaszonyiPrinter().print(graphList,outputFilePath,informationFromFile,
                                                NO_APPEND);
                        break;
                    default:
                        std::cout << "Something went wrong" << std::endl;
                }
            } catch (std::exception &e){
                std::cerr << "Problem was caused by exception: " << e.what() << std::endl;
                QMessageBox exceptionMessageBox;
                exceptionMessageBox.setWindowTitle("Exception window");
                exceptionMessageBox.setText("An error occurred in file: "
                                            + fileName + "\n\n"
                                            "Please make sure the graphs in the file are defined correctly and try it again");
                exceptionMessageBox.exec();
            }
    }

    emit enableMainWindow(this);
}

QtGraphProgramManager::QtGraphProgramManager(QWidget *parent) {
    this->setObjectName("GraphProgramManager");
}
