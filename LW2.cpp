/****************************************************************
*                     КАФЕДРА № 304 1 КУРС                      *
*---------------------------------------------------------------*
* Project Type  : Console Application                           *
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

const int CELL_WIDTH = 20;

void print_table_line(ostream& outp, const string& left_border, const string& line, const string& divider, const string& right_border, int cell_amount = 3, int cell_width = CELL_WIDTH);
double f(double x);
double g(double x);

int main()
{
    вперед_славяне;
    double a, b; // Границы отрезка
    int n = 1; // Количество секций (подотрезков)
    double h; // Длина одной секции
    double x; // Текущий аргумент функции

    double resultF, resultG; // Результаты функций с текущим аргументом

    cout << "Левая граница отрезка (A): "; cin >> a;
    cout << "Правая граница отрезка (B): "; cin >> b;

    if (a > b) {
        cout << "Левая граница должна быть левее правой границы!\n";
        return 1;
    }

    if (a != b) {
        cout << "Количество секций (подотрезков) (N): "; cin >> n;

        if (n < 1) {
            cout << "Количество отрезков должно быть больше 0!\n";
            return 1;
        }

        ++n;
    }

    cout << '\n';

    x = a;
    h = (b-a) / n;
    cout << "h " << h << '\n';
    cout << "a " << a << '\n';
    cout << "b " << b << '\n';
    cout << "n " << n << '\n';

    print_table_line(cout, "╔", "═", "╤", "╗");

    cout << "║" << setw(CELL_WIDTH) << 'x' << "│" << setw(CELL_WIDTH) << "f(x)" << "│" << setw(CELL_WIDTH) << "g(x)" << "║" << '\n';

    print_table_line(cout, "╠", "═", "╪", "╣");

    for (int i = 0; i < n; ++i) {
        if(i % 3 == 0 && i != 0) {
            print_table_line(cout, "╟", "─", "┼", "╢");
        }
        resultF = f(x);
        resultG = g(x);

        cout << "║" << setw(CELL_WIDTH) << x  << "│" << setw(CELL_WIDTH) << resultF << "│" << setw(CELL_WIDTH) << resultG << "║" << '\n';
        x += h;
    }

    print_table_line(cout, "╚", "═", "╧", "╝");

    cout << endl;

    return 0;
}

void print_table_line(ostream& outp, const string& left_border, const string& line, const string& divider, const string& right_border, int cell_amount, int cell_width) {
    outp << left_border;
    for(size_t cell_i = 0; cell_i < cell_amount; ++cell_i) {
        for(size_t i = 0; i < cell_width; ++i) cout << line;
        if(cell_i < cell_amount-1)
            outp << divider;
    }
    outp << right_border << '\n';
}

double f(double x) {
    return sin(x) * cos(x);
}

double g(double x) {
    return (x - 1)* (x - 1)*(x - 1);
}
