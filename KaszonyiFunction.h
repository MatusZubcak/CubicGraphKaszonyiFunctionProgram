//
// Created by Dell on 25. 10. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_KASZONYIFUNCTION_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_KASZONYIFUNCTION_H

#include <set>
#include "Edge.h"

class KaszonyiFunction{

public:
    virtual int getKaszonyiValue(std::set<unsigned int>& vertices,
                                 std::set<Edge>& edges,
                                 unsigned int numberOfIsolatedCircles) = 0;
    virtual int getKaszonyiValue(std::set<unsigned int>& vertices,
                                 std::set<Edge>& edges) = 0;
    virtual ~KaszonyiFunction()= default;;

};

#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_KASZONYIFUNCTION_H
