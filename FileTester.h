//
// Created by Dell on 22. 11. 2021.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_FILETESTER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_FILETESTER_H


#include <string>

class FileTester {
public:

    //compareFiles should be private
    bool compareFiles(const std::string& filename1, const std::string& filename2);
    FileTester()=default;;

};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_FILETESTER_H
