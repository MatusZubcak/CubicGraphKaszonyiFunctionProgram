//
// Created by Dell on 12. 10. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHEXCEPTIONS_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHEXCEPTIONS_H


#include <exception>

struct EdgeMinimalMultiplicityException : std::exception {
    const char *what() const noexcept override;
};

struct EdgeMaximalMultiplicityException : std::exception {
    const char *what() const noexcept override;
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHEXCEPTIONS_H
