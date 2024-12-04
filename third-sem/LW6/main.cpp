/******************************************************************
*                     КАФЕДРА № 304 2 КУРС                        *
*-----------------------------------------------------------------*
* Project Type  : Win32 Console Application                       *
* Project Name  : BinarySearchTrees                               *
* File Name     : main.cpp                                        *
* Language      : C/C++                                           *
* Programmer(s) : Романов Д.И., Ильин А.А                         *
* Modified By   :                                                 *
* Created       : 20/09/2024                                      *
* Last Revision : 15/11/2024                                      *
* Comment(s)    : Бинарные деревья поиска                         *
******************************************************************/

#include <iostream>

#include "binary_tree.h"
#include "helpers.h"
#include "random_tree.h"

const int ARR_LEN = 24;
const int ARR_MIN = 1;
const int ARR_MAX = 50;

int main() {
    std::cout << "Лабораторная работа №2 - Линейные списки\n";
    std::cout << "    Вариант №9\n";

//    auto vec = generate_array(ARR_LEN, ARR_MIN, ARR_MAX);
    auto vec = {31, 33, 11, 5, 13, 39, 29, 23, 7, 27, 19, 41, 1, 3, 25, 47, 21, 35, 43, 45, 9, 15, 17, 37};

    std::cout << "Изначальный массив: ";

    for (auto val: vec) {
        std::cout << val << ' ';
    }
    std::cout << '\n';


    srand(1);
    btree::node *binary_tree{nullptr};
    for (auto val: vec) {
        binary_tree = btree::insert(binary_tree, val);
        btree::print_tree(binary_tree);
    }

    std::cout << "Бинарное дерево поиска. Высота: " << btree::height(binary_tree) << "\n";
    btree::print_tree(binary_tree);


    srand(1);
    rtree::node *random_tree{nullptr};
    for (auto val: vec) {
        random_tree = rtree::insert(random_tree, val);
    }

    std::cout << "Случайное бинарное дерево поиска. Высота: " << rtree::height(random_tree) << "\n";
    rtree::print_tree(random_tree);

    return 0;
}
