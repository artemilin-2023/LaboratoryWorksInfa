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

    cout << "╔";
    for(size_t i = 0; i < 20; ++i) cout << "═";
    cout << "╤";
    for(size_t i = 0; i < 20; ++i) cout << "═";
    cout << "╤";
    for(size_t i = 0; i < 20; ++i) cout << "═";
    cout << "╗" << '\n';

    cout << "║" << setw(20) << 'x' << "│" << setw(20) << "f(x)" << "│" << setw(20) << "g(x)" << "║" << '\n';

    cout << "╠";
    for(size_t i = 0; i < 20; ++i) cout << "═";
    cout << "╪";
    for(size_t i = 0; i < 20; ++i) cout << "═";
    cout << "╪";
    for(size_t i = 0; i < 20; ++i) cout << "═";
    cout << "╣" << '\n';

    for (int i = 0; i < n+1; ++i) {
        if(i % 3 == 0 && i != 0) {
            cout << "╟";
            for(size_t i = 0; i < 20; ++i) cout << "─";
            cout << "┼";
            for(size_t i = 0; i < 20; ++i) cout << "─";
            cout << "┼";
            for(size_t i = 0; i < 20; ++i) cout << "─";
            cout << "╢" << '\n';
        }
        resultF = f(x);
        resultG = g(x);

        cout << "║" << setw(20) << x  << "│" << setw(20) << resultF << "│" << setw(20) << resultG << "║" << '\n';
        x += h;
    }

    cout << "╚";
    for(size_t i = 0; i < 20; ++i) cout << "═";
    cout << "╧";
    for(size_t i = 0; i < 20; ++i) cout << "═";
    cout << "╧";
    for(size_t i = 0; i < 20; ++i) cout << "═";
    cout << "╝" << '\n';

    system("pause");
    return 0;
}

double f(double x) {
    return sin(x) * cos(x);
}

double g(double x) {
    return (x - 1)* (x - 1)*(x - 1);
}
