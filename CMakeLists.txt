cmake_minimum_required(VERSION 3.14)
project(CubicGraphKaszonyiFunctionProgram)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(CubicGraphKaszonyiFunctionProgram
        main.cpp
        Tests.cpp
        Tests.h
        Edge.cpp
        Edge.h
        GraphExceptions.cpp
        GraphExceptions.h
        CubicGraph.cpp
        CubicGraph.h
        ColoringFinder/ColoringFinder.h
        ColoringFinder/FactorColoringFinder.cpp
        ColoringFinder/FactorColoringFinder.h
        GraphLoader/GraphLoader.h
        GraphPrinter/KaszonyiPrinterTimesThree.cpp
        GraphPrinter/KaszonyiPrinterTimesThree.h
        Enums.h
        GraphPrinter/GraphPrinter.h
        GraphPrinter/GraphPrinter.h
        GraphPrinter/SequentialPathPrinter.cpp
        GraphPrinter/SequentialPathPrinter.h
        GraphPrinter/GraphPrinter.cpp
        Suppression/Suppression.h
        Suppression/SequentialSuppressionNaive.cpp
        Suppression/SequentialSuppressionNaive.h
        GraphPrinter/ParallelPathPrinter.cpp
        GraphPrinter/ParallelPathPrinter.h
        Suppression/ParallelSuppressionNaive.cpp
        Suppression/ParallelSuppressionNaive.h
        Suppression/SequentialSuppressionMemoized.cpp
        Suppression/SequentialSuppressionMemoized.h
        Hash.h
        Suppression/Suppression.cpp
        Suppression/ParallelSuppressionMemoized.cpp
        Suppression/ParallelSuppressionMemoized.h
        AutomatedSuppressionTester.cpp
        AutomatedSuppressionTester.h
        GraphPrinter/ResistancePrinter.cpp
        GraphPrinter/ResistancePrinter.h
        ColoringFinder/SATColoringFinder.cpp
        ColoringFinder/SATColoringFinder.h
        GraphLoader/GraphLoader.cpp
        CMSat/cryptominisat.h
        CMSat/solvertypesmini.h
        Qt/QtExitButton.cpp
        Qt/QtExitButton.h
        Qt/QtCancelButton.cpp
        Qt/QtCancelButton.h
        Qt/QtMenuWindow.cpp
        Qt/QtMenuWindow.h
        Qt/QtClearButton.cpp
        Qt/QtClearButton.h
        Qt/QtRemoveButton.cpp
        Qt/QtRemoveButton.h
        Qt/QtFileList.cpp
        Qt/QtFileList.h Qt/QtChooseFilesButton.cpp Qt/QtChooseFilesButton.h Qt/QtFileWindow.cpp Qt/QtFileWindow.h Qt/QtRunButton.cpp Qt/QtRunButton.h Qt/QtOutputDirectoryButton.cpp Qt/QtOutputDirectoryButton.h Qt/QtDirectoryWindow.cpp Qt/QtDirectoryWindow.h Qt/QtGraphProgramManager.cpp Qt/QtGraphProgramManager.h GraphPrinter/KaszonyiPrinterOriginal.cpp GraphPrinter/KaszonyiPrinterOriginal.h ColoringFinder/PDColoringFinder.cpp ColoringFinder/PDColoringFinder.h)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

include_directories("/usr/local/lib")

target_link_libraries(CubicGraphKaszonyiFunctionProgram
        "/usr/local/lib/libcryptominisat5.so"
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets)
