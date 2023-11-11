/****************************************************************
*                     КАФЕДРА № 304 1 КУРС                      *
*---------------------------------------------------------------*
* Project Type  : Win32 Console Application                     *
* Project Name  : LW1                                           *
* File Name     : LW1.cpp                                       *
* Language      : C/C++                                         *
* Programmer(s) : Романов Д.И., Ильин А.А                       *
* Created at    : 27/10/23                                      *
* Last Revision : 09/11/23                                      *
* Comment(s)    : Вычисление суммы бесконечного числового ряда. *
****************************************************************/

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    // Инициалилизация переменных
    const double targetSum = 0.970962 - 0.01;//M_PI * M_PI * M_PI / 32; // Точная сумма

    int n = 0; // Текущая иитерация
    int sign = -1; // Знак
    double currentSum = 0; // Текущая сумма
    double diff = abs(targetSum - currentSum); // Разница между текущей и точной суммой
    double addTerm = 0; // Слогаемое на текущей итерации.

    double epsilon; // Заданная точность

    // Ввод epsilon
    cout << "Enter the epsilon to use: "; cin >> epsilon;

    // Контроль входных данных
    if (epsilon <= 0) {
        cout << "Epsilon should be greater than 0!\n";
        system("pause");
        return 1;
    }

    // Цикл нахождения суммы ряда,
    // проверка найдено ли искомое значение с учетом введенного epsilon
    while (diff > epsilon)
    {
        n += 1;
        // -1 в степени n означает смену знака слагаемого каждую итерацию суммы
        sign = -sign;


        // Вместо домножения слагаемого на знак можно сразу поделить знак
        // (он может быть только 1 или -1)
        addTerm = sign / ((2.0 * n - 1.0) * (2.0 * n - 1.0) * (2.0 * n - 1.0));
        currentSum += addTerm;
        diff = abs(targetSum - currentSum);

#ifdef _DEBUG
        cout << "current iteration = " << n << "; ";
        cout << "current sum = " << currentSum << "; ";
        cout << "current term = " << addTerm << "; ";
        cout << "current diff = " << diff << '\n';
#endif
        // Расчёт текущего отклонения от искомого значения
    }

    // Вывод найденных значений
    cout << "Precalculated target sum: " << targetSum << '\n';
    cout << "Amount of iterations/terms: " << n << '\n';
    cout << "Entered epsilon is " << epsilon
         << ", and the difference at the end is " << diff << '\n';
    cout << "Found sum: " << currentSum << '\n';

    system("pause");
    return 0;
}
