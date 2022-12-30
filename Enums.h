//
// Created by Dell on 2. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_ENUMS_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_ENUMS_H

// different enums used in the program
enum append{
    APPEND,
    NO_APPEND
};

enum suppression{
    PARALLEL,
    SEQUENTIAL
};

enum edgesFormat{
    MARK_ORIGINAL_EDGES,
    IGNORE_EDGE_ORIGINALITY
};

enum coloringAlgorithm{
    SAT,
    FACTOR,
    PD,
    ANY
};

enum colorPrintFormat{
    COLORING_EXISTS,
    COLORING_NUMBER_TIMES_THREE,
    COLORING_NUMBER_ORIGINAL
};

#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_ENUMS_H
