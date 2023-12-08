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

void print_table_line(ostream& output, const string& left_border, const string& line, const string& divider, const string& right_border, int cell_amount = 4, int cell_width = CELL_WIDTH);
double f(double x);
double g(double x);

int main()
{
    вперед_славяне;
    double a, b; // Границы отрезка
    int n = 0; // Количество интервалов
    double h; // Длина одной секции
    double x; // Текущий аргумент функции

    double resultF, resultG; // Результаты функций с текущим аргументом

    cout << "Левая граница отрезка (A): "; cin >> a;
    cout << "Правая граница отрезка (B): "; cin >> b;

    // Проверка диапазона на корректность
    if (a > b)
    {
        cerr << "Левая граница должна быть левее правой границы!\n";
        return 1;
    }

    // Начало не совпадает с концом отрезка => количество точек (n) > 1
    if (a != b)
    {
        cout << "Количество секций (подотрезков) (N): "; cin >> n;

        // Проверка на корректность
        if (n < 1)
        {
            cerr << "Количество отрезков должно быть больше 0!\n";
            return 2;
        }
    }

    cout << '\n';

    // Инициализация
    //x = a;
    h = (b-a) / n;

    // Вывод заголовка таблицы
    print_table_line(cout, "╔", "═", "╤", "╗");
    cout << "║" << setw(CELL_WIDTH) << 'N' << "│" << setw(CELL_WIDTH) << 'x' << "│" << setw(CELL_WIDTH) << "f(x)" << "│" << setw(CELL_WIDTH) << "g(x)" << "║" << '\n';
    print_table_line(cout, "╠", "═", "╪", "╣");

    // int eps = h/10;
    // while(x <= B + eps) { // ... }

    // int i = 0;
    // while(i <= N) { // ...; i++; }
    for (int i = 0; i <= n; ++i)
    {
        x = a + i * h; // Переход к следующей точке

        if(i % 3 == 0 && i != 0) // Каждая третья строка таблицы отчерчивается линией
        {
            print_table_line(cout, "╟", "─", "┼", "╢");
        }

        // Расчет значений функций в зависимости от текущего x
        resultF = f(x);
        resultG = g(x);

        // Вывод значений
        cout << "║" << setw(CELL_WIDTH) << i  << "│" << setw(CELL_WIDTH) << x  << "│" << setw(CELL_WIDTH) << resultF << "│" << setw(CELL_WIDTH) << resultG << "║" << '\n';

        // x += h; // Смещение текущего x на шаг h
        // i++;
    }

    // Вывод нижней границы таблицы
    print_table_line(cout, "╚", "═", "╧", "╝");

    return 0;
}

void print_table_line(ostream& output, const string& left_border, const string& line, const string& divider, const string& right_border, int cell_amount, int cell_width) {
    output << left_border;
    for(size_t cell_i = 0; cell_i < cell_amount; ++cell_i)
    {
        for(size_t i = 0; i < cell_width; ++i) cout << line;
        if(cell_i < cell_amount-1)
            output << divider;
    }

    output << right_border << endl;
}

double f(double x) {
    return sin(x) * cos(x);
}

double g(double x) {
    return (x - 1)*(x - 1)*(x - 1);
}
