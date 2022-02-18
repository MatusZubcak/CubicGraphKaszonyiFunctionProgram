//
// Created by matus on 4. 2. 2022.
//

#include "DirectoryReader.h"
#include <filesystem>
#include <iostream>
#include <algorithm>

std::vector<std::string> DirectoryReader::fileList(const std::string &directoryPath) {
    std::vector<std::string> fileList;

    //Iterate through all files in directory
    for(const auto & entry : std::filesystem::directory_iterator(directoryPath)){
        //If entry is regular file, add it to fileList
        if( entry.is_regular_file() ) fileList.push_back( std::filesystem::absolute( entry.path() ).string() );
    }

    std::sort(fileList.begin(), fileList.end());
    return fileList;
}
