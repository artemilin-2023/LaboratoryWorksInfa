/****************************************************************
*                     КАФЕДРА № 304 1 КУРС                      *
*---------------------------------------------------------------*
* Project Type  : Console Application                           *
* Project Name  : LW3                                           *
* File Name     : LW3.cpp                                       *
* Language      : C/C++                                         *
* Programmer(s) : Романов Д.И., Ильин А.А                       *
* Created at    : 03/12/23                                      *
* Last Revision : 03/12/23                                      *
* Comment(s)    : Одномерные массивы.                           *
****************************************************************/


#define вперед_славяне setlocale(LC_ALL, "ru_RU.UTF-8")

#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

const int ARRAY_LENGTH = 10;
const string FILE_NAME = "data.txt";

int count_file_elements(ifstream &in);

int main()
{
    вперед_славяне;

    double P = 0;
    int N = 0;
    double vec[ARRAY_LENGTH] = {0};
    double new_vec[ARRAY_LENGTH] = {0};

    double new_item;
    double positive_nums_sum = 0;
    double last_n_elements_sum = 0;

    double min_value = INT_MAX;
    double max_value = INT_MIN;
    int pos_min = 0;
    int pos_max = 0;

    ifstream file(FILE_NAME);
    if (!file.is_open())
    {
        cerr << "Ошибка открытия файла.";
        return -1;
    }
    else if (file.peek() == EOF)
    {
        cerr << "Файл пуст";
        file.close();
        return -2;
    }
    else if (count_file_elements(file) < 3)
    {
        cerr << "В файле недостаточно элементов, минимальное количество - 3";
        file.close();
        return -3;
    }

    file >> P >> N;
    cout << "P: " << P << "\n" << "N: " << N << "\n";
    if (N <= 0)
    {
        cerr << "N должно быть больше 0!";
        file.close();
        return -4;
    }

    cout << "Исходный массив: ";
    int j = 0;
    while (file >> new_item && j < ARRAY_LENGTH)
    {
        if (new_item > 0 && j < N)
            positive_nums_sum += new_item;

        vec[j++] = new_item;
        cout << new_item << " ";
    }
    file.close();
    cout << "\n";

    for (int i = 0; i < ARRAY_LENGTH; i++)
    {
        new_vec[i] = P + vec[i] + positive_nums_sum;
    }


    N = min(N, ARRAY_LENGTH);
    for (int i = ARRAY_LENGTH - N; i < ARRAY_LENGTH; i++)
        last_n_elements_sum += new_vec[i];

    cout << "Сформированный массив: ";
    for (int i = 0; i < ARRAY_LENGTH; i++)
    {
        if (min_value > new_vec[i])
        {
            min_value = new_vec[i];
            pos_min = i;
        }
        if (max_value < new_vec[i])
        {
            max_value = new_vec[i];
            pos_max = i;
        }

        cout << new_vec[i] << ' ';
    }
    cout << "\n\n";

    cout << "Минимальный элемент " << min_value << " находится в массиве под индексом " << pos_min << '\n';
    cout << "Максимальный элемент " << max_value << " находится в массиве под индексом " << pos_max << '\n';
    cout << "Сумма последних " << N << " элементов: " << last_n_elements_sum << endl;

    return 0;
}

int count_file_elements(ifstream &in)
{
    double x;
    int counter = 0;
    while(in >> x) counter++;

    // сброс позиции считывания к изначальному
    in.clear();
    in.seekg(0L, std::ios_base::beg);

    return counter;
}


