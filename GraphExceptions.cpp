//
// Created by Dell on 12. 10. 2021.
//

#include "GraphExceptions.h"

const char* BadlyDefinedGraphException::what() const noexcept
{
    return "Badly defined Graph exception";
}

const char *EdgeMinimalMultiplicityException::what() const noexcept {
    return "Edge multiplicity can't be decremented because it already has minimal viable multiplicity";
}

const char *EdgeMaximalMultiplicityException::what() const noexcept {
    return "Edge multiplicity can't be incremented because it already has maximal viable multiplicity of 3";
}