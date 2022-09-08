//
// Created by Dell on 12. 10. 2021.
//

#include "GraphExceptions.h"

// Exceptions for different problems that can occur during graph loading from file
// also includes exceptions that can occur while the program is running
// exception names should be enough descriptive to not need any other comme
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

const char* FileCannotBeOpenedException::what() const noexcept
{
    return "Unable to open file";
}

const char* ConversionFromListToSequenceFailed::what() const noexcept
{
    return "While converting list of all generated graphs to the final suppression sequence an error occured";
}

const char *ExpectedDepthListWrongSize::what() const noexcept {
    return "Size of the expected depth values is different from the number of graphs located in the file";
}

const char *KaszonyiValueNotDivisibleByThreeException::what() const noexcept {
    return "Kaszonyi value is not divisible by three";
}
