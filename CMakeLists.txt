cmake_minimum_required(VERSION 3.17)
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
        ColoringFinder.h
        ColoringFinderFactor.cpp
        ColoringFinderFactor.h
        GraphLoader.h
        GraphLoaderSimpleAdjListsFormat.cpp
        GraphLoaderSimpleAdjListsFormat.h
        KaszonyiValuesPrinter.cpp
        KaszonyiValuesPrinter.h
        Enums.h
        GraphPrinter.h
        GraphPrinter.h
        ControlSequentialFormatPrinter.cpp
        ControlSequentialFormatPrinter.h
        GraphPrinter.cpp
        ContinuousSuppression.h
        SequentialSuppressionNaive.cpp
        SequentialSuppressionNaive.h
        ControlParallelFormatPrinter.cpp
        ControlParallelFormatPrinter.h
        ParallelSuppressionNaive.cpp
        ParallelSuppressionNaive.h
        SequentialSuppressionMemoized.cpp
        SequentialSuppressionMemoized.h
        Hash.h
        ContinuousSuppression.cpp
        ParallelSuppressionMemoized.cpp
        ParallelSuppressionMemoized.h
        AutomatedSuppressionTester.cpp
        AutomatedSuppressionTester.h
        ResistanceValuesPrinter.cpp
        ResistanceValuesPrinter.h
        ColoringFinderSAT.cpp
        ColoringFinderSAT.h
        GraphLoaderIndexedAdjListsWithDescription.cpp
        GraphLoaderIndexedAdjListsWithDescription.h
        GraphLoader.cpp
        DirectoryReader.cpp
        DirectoryReader.h
        cryptominisat.h
        solvertypesmini.h)

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