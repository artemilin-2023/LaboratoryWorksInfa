/****************************************************************
*                     КАФЕДРА № 304 1 КУРС                      *
*---------------------------------------------------------------*
* Project Type  : Console Application				*
* Project Name  : LW2                                           *
* File Name     : LW2.cpp                                       *
* Language      : C/C++                                         *
* Programmer(s) : Романов Д.И., Ильин А.А                       *
* Created at    : 11/11/23                                      *
* Last Revision : 11/11/23                                      *
* Comment(s)    : Табулирование функций.                        *
****************************************************************/

#define _USE_MATH_DEFINES
#define вперед_славяне setlocale(LC_ALL, "ru_RU.UTF-8")

#include <iostream>
#include <cmath>
#include <iomanip>
#include "fort.hpp"

using namespace std;

double f(double x);
double g(double x);

int main()
{
    вперед_славяне;
    double a, b; // Границы отрезка
    int n = 0; // Количество секций (подотрезков)
    double h; // Длина одной секции
    double x; // Текущий аргумент функции

    double resultF, resultG; // Результаты функций с текущим аргументом

    fort::char_table table;

    cout << "Левая граница отрезка (A): "; cin >> a;
    cout << "Правая граница отрезка (B): "; cin >> b;

    if (a > b) {
        cout << "Левая граница должна быть левее правой границы!\n";
        system("pause");
        return 1;
    }

    if (a != b) {
        cout << "Количество секций (подотрезков) (N): "; cin >> n;

        if (n < 1) {
            cout << "Количество отрезков должно быть больше 0!\n";
            system("pause");
            return 1;
        }
    }

    cout << '\n';

    x = a;
    h = (b-a) / n;

    table.set_cell_text_align(fort::text_align::center);
    table.set_border_style(FT_SIMPLE_STYLE);
    table.set_cell_left_padding(3);
    table.set_cell_right_padding(3);

    table << fort::header << "x" << "f(x)" << "g(x)" << fort::endr;

    for (int i = 0; i < n+1; ++i) {
        if(i % 3 == 0 && i != 0) {
            table << fort::separator;
        }
        resultF = f(x);
        resultG = g(x);

        table << x << resultF << resultG << fort::endr;

        x += h;
    }

    cout << table.to_string() << '\n';

    system("pause");
    return 0;
}

double f(double x) {
    return sin(x) * cos(x);
}

double g(double x) {
    return (x - 1)* (x - 1)*(x - 1);
}
