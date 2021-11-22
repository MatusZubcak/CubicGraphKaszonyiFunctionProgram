//
// Created by Dell on 22. 11. 2021.
//

#include <fstream>
#include <iostream>
#include "FileTester.h"
#include "GraphExceptions.h"

bool FileTester::compareFiles(const std::string& filename1, const std::string& filename2) {
    std::ifstream f1, f2;
    f1.open(filename1);
    f2.open(filename2);
    bool areSame = true;

    try {
        if (!f1 || !f2) {
            throw FileCannotBeOpenedException();
        }

        std::string str1, str2;
        while( f1 >> str1 && f2 >> str2){
            if(str1 != str2)
                areSame = false;
        }
        if( f1 >> str1 || f2 >> str2)
            areSame = false;

        f2.close();
        f1.close();
    } catch (std::exception &e) {
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        f1.close();
        f2.close();
    }

    return areSame;
}
