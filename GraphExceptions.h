//
// Created by Dell on 12. 10. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHEXCEPTIONS_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHEXCEPTIONS_H


#include <exception>

// Exceptions for different problems that can occur during graph loading from file
// also includes exceptions that can occur while the program is running
// exception names should be enough descriptive to not need any other comments
struct BadlyDefinedGraphException : std::exception {
    const char *what() const noexcept override;
};

struct EdgeMinimalMultiplicityException : std::exception {
    const char *what() const noexcept override;
};

struct EdgeMaximalMultiplicityException : std::exception {
    const char *what() const noexcept override;
};

struct LoopSuppressionException : std::exception {
    const char *what() const noexcept override;
};

struct EdgeDoesNotExistException : std::exception {
    const char *what() const noexcept override;
};

struct VertexNotIncidentException : std::exception {
    const char *what() const noexcept override;
};

struct GraphloaderEmptyException : std::exception {
    const char *what() const noexcept override;
};

struct WrongNumberOfVerticesException : std::exception {
    const char* what() const noexcept override;
};

struct BadFileEndingException : std::exception{
    const char* what() const noexcept override;
};

struct FileCannotBeOpenedException : std::exception{
    const char* what() const noexcept override;
};

struct ConversionFromListToSequenceFailed : std::exception{
    const char* what() const noexcept override;
};

struct ExpectedDepthListWrongSize : std::exception{
    const char* what() const noexcept override;
};
#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_GRAPHEXCEPTIONS_H
