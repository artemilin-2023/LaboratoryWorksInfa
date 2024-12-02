/****************************************************************
 *                     КАФЕДРА № 304 1 КУРС                      *
 *---------------------------------------------------------------*
 * Project Type  : Win32 Console Application                     *
 * Project Name  : LW2                                           *
 * File Name     : LW2.cpp                                       *
 * Language      : C/C++                                         *
 * Programmer(s) : Романов Д.И., Ильин А.А                       *
 * Created at    : 20/02/24                                      *
 * Last Revision : 05/03/24                                      *
 * Comment(s)    : Двумерные массивы                             *
 ****************************************************************/

#include <iostream>
#include <fstream>
#include <limits>

#include "helpers.h"

int main(int argc, char **argv) {
    if(argc != 3) {
        std::cout << "Usage: " << argv[0] << " test_file_A test_file_B" << '\n';
        return 0;
    }

    std::cout << "Файл 1: " << argv[1] << '\n';
    handle_file(argv[1]);

    std::cout << "Файл 2: " << argv[2] << '\n';
    handle_file(argv[2]);
}

