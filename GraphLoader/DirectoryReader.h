//
// Created by matus on 4. 2. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_DIRECTORYREADER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_DIRECTORYREADER_H


#include <vector>
#include <string>

// old class that finds all filenames from given directory
// currently obsoleted because Qt graphical interface provides the program only with files
class DirectoryReader {
public:
    std::vector<std::string> fileList(const std::string &directoryPath);

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_DIRECTORYREADER_H
