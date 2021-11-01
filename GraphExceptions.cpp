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

const char *LoopSuppressionException::what() const noexcept {
    return "Loop can't be suppressed";
}

const char *EdgeDoesNotExistException::what() const noexcept {
    return "Edge can't be suppressed because it does not exist";
}

const char *VertexNotIncidentException::what() const noexcept {
    return "Second vertex can't be found because edge is not incident with entered vertex";
}

const char *GraphloaderEmptyException::what() const noexcept {
    return "You tried to get element from empty GraphLoader";
}

const char* WrongNumberOfVerticesException::what() const noexcept
{
    return "Bad number of vertices in file from which you tried loading CubicGraph";
}

const char* BadFileEndingException::what() const noexcept
{
    return "There is a small amount of remaining adjacency lists at the end of the file that cannot belong to any graph of given size";
}