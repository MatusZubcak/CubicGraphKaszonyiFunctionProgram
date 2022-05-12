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
QtGraphProgramManager::runGraphProgram(int formatType, QStringList filePaths, QString outputDirectory) {
    AdjListsGraphLoader adjListsGraphLoader = AdjListsGraphLoader();
    std::string informationFromFile;
    std::vector<CubicGraph> graphList;


    for(QString &filePath : filePaths){
        QString fileName = filePath.section('/', -1);
            std::string outputFilePath = outputDirectory.toStdString() + "/" + fileName.toStdString();
            try{
                graphList = adjListsGraphLoader.loadNewGraphs(filePath.toStdString(), informationFromFile);

                switch(formatType){
                    case 0:
                        outputFilePath += ".res";
                        ResistancePrinter().print(graphList,outputFilePath,informationFromFile,
                                                  NO_APPEND);
                        break;
                    case 1:
                        outputFilePath += ".ppath";
                        ParallelPathPrinter().print(graphList,outputFilePath,informationFromFile,
                                                    NO_APPEND);
                        break;
                    case 2:
                        outputFilePath += ".spath";
                        SequentialPathPrinter().print(graphList,outputFilePath,informationFromFile,
                                                      NO_APPEND);
                        break;
                    case 3:
                        outputFilePath += ".kas";
                        KaszonyiPrinter().print(graphList,outputFilePath,informationFromFile,
                                                NO_APPEND);
                        break;
                    default:
                        std::cout << "Something went wrong" << std::endl;
                }
            } catch (std::exception &e){
                std::cerr << "Problem was caused by exception: " << e.what() << std::endl;
                emit castException(fileName);
            }
    }

    emit enableMainWindow();
}

QtGraphProgramManager::QtGraphProgramManager(QObject *parent) : QObject(parent) {
    this->setObjectName("GraphProgramManager");
}
