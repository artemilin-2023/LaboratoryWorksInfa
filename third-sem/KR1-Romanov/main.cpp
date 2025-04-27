/******************************************************************
*                     КАФЕДРА № 304 2 КУРС                        *
*-----------------------------------------------------------------*
* Project Type  : Win32 Console Application                       *
* Project Name  : Database                                        *
* File Name     : main.cpp                                        *
* Language      : C/C++                                           *
* Programmer(s) : Романов Д.И.                                    *
* Modified By   :                                                 *
* Created       : 01/12/2024                                      *
* Last Revision : 15/12/2024                                      *
* Comment(s)    : Линейные списки                                 *
******************************************************************/

#include <iostream>

#include "menu.h"
#include "database.h"

int main() {
    std::cout << "Курсовая Работа - Романов Денис Игоревич\n";
    std::cout << "    Вариант №7\n";

    auto *database = new db::database{};
    std::cout << "Создана пустая база данных\n";

    // main menu loop
    menu::use_main_menu(database);
    return 0;
}
