/******************************************************************
*                     КАФЕДРА № 304 2 КУРС                        *
*-----------------------------------------------------------------*
* Project Type  : Win32 Console Application                       *
* Project Name  : Sequences                                       *
* File Name     : main.cpp                                        *
* Language      : C/C++                                           *
* Programmer(s) : Романов Д.И., Ильин А.А                         *
* Modified By   :                                                 *
* Created       : 20/09/2024                                      *
* Last Revision : 05/10/2024                                      *
* Comment(s)    : Формирование массивов экспериментальных данных  *
******************************************************************/

#include <iostream>

#include "types.h"
#include "sequences.h"
#include "functions.h"

#define START_X 0 // Начальное значение X
#define COUNT_X 100 // Количество элементов в массиве
#define STEP_X 0.1 // Шаг X для дробных функций

const int array_sizes[] = {
    5  * 100000,
    10 * 100000,
    15 * 100000,
    20 * 100000,
    25 * 100000,
    30 * 100000,
    35 * 100000,
    40 * 100000,
    45 * 100000,
    50 * 100000,
};

using namespace std;

int main()
{
    srand(time(nullptr));

    IntFunc intFuncs[] = { ordered, orderBack, randomized, saw, step, quasi }; // Целочисленные последовательности
    DoubleFunc doubleFuncs[] = { ordered, orderBack, randomized, saw, step, sinusoid, quasi }; // Десятичные последовательности

    for (auto& intFunc : intFuncs) { // Создание массивов и запись в файл для целочисленных функций
        IntPoint* arr = GenerateArray(START_X, COUNT_X, intFunc);
        WriteArrayToFile(arr, COUNT_X - 1, GetFilename());
    }

    for (auto& doubleFunc : doubleFuncs) { // Создание массивов и запись в файл для десятичных  функций
        DoublePoint* arr = GenerateArray(START_X, COUNT_X, STEP_X, doubleFunc);
        WriteArrayToFile(arr, COUNT_X - 1, GetFilename());
    }
    ofstream fout(GetFilename());
    for (auto& f : intFuncs) { // Измерение времени создания целочисленных последовательностей
        //ofstream fout(GetFilename());
        for (auto& size : array_sizes) {
            fout << fixed << setprecision(3) << GetAverageExecutionTime(f, size) << ' ';
        }
        fout << endl;
    }
    fout.close();
    ofstream fout2(GetFilename());
    for (auto& f : doubleFuncs) { // Измерение времени создания вещественных последовательностей
        //ofstream fout(GetFilename());
        for (auto& size : array_sizes) {
            fout2 << fixed << setprecision(3) << GetAverageExecutionTimefordouble(f, STEP_X, size) << ' ';
        }
        fout2 << endl;
        //fout.close();
    }
    fout2.close();

    return 0;
}
