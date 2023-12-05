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


const int ARRAY_LENGTH = 10; // длина массива
const string FILE_NAME = "data.txt"; // имя файла

int count_file_elements(ifstream &in);
bool data_is_valid(ifstream  &in);
void reset_stream(ifstream &stream);
bool is_numeric(const string& str);

int main()
{
    вперед_славяне;

    // объявление, инициализация переменных
    double P = 0; // элемент суммы при формировании нового массива
    int N = 0; // количество N первых или N последних (см. условие)
    double vec[ARRAY_LENGTH] = {0}; // исходный массив
    double new_vec[ARRAY_LENGTH] = {0}; // новый массив

    double new_item; // новый элемент в массиве
    double positive_nums_sum = 0; // сумма положительных чисел
    double last_n_elements_sum = 0; // сумма последних N элементов

    double min_value = INT_MAX; // минимальное число
    double max_value = INT_MIN; // максимальное число
    int pos_min = 0; // позиция минимального числа
    int pos_max = 0; // позиция максимального числа

    int j = 0; // счетчик для цикла

    ifstream file(FILE_NAME); // создание потока для чтения
    if (!file.is_open()) // файл не найден
    {
        cerr << "Ошибка открытия файла.";
        file.close(); // закрыть поток чтения
        return -1;
    }
    else if (file.peek() == EOF) // файл не содержит данных
    {
        cerr << "Файл пуст";
        file.close();
        return -2;
    }
    else if (count_file_elements(file) < 12) // файл содержит недостаточное количество данных
    {
        cerr << "В файле недостаточно элементов, минимальное количество - 12";
        file.close();
        return -3;
    }
    else if (!data_is_valid(file)) // файл содержит буквенные/спец символы
    {
        cerr << "Ошибка данных: невозможно привести к типу  double";
        file.close();
        return -4;
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
    while (file >> new_item && j < ARRAY_LENGTH) // чтение данных из файла и занесение их в массив
    {
        if (new_item > 0 && j < N) // суммирование первых N положительных элементов
            positive_nums_sum += new_item;

        vec[j++] = new_item;
        cout << new_item << " ";
    }
    file.close();
    cout << "\n";

    for (int i = 0; i < ARRAY_LENGTH; i++) // расчет новых значений для new_vec
    {
        new_vec[i] = P + vec[i] + positive_nums_sum;
    }

    // N не может быть больше, чем длина массива
    N = min(N, ARRAY_LENGTH);
    for (int i = ARRAY_LENGTH - N; i < ARRAY_LENGTH; i++) // суммирование N последних элементов
        last_n_elements_sum += new_vec[i];

    cout << "Сформированный массив: ";
    for (int i = 0; i < ARRAY_LENGTH; i++)
    {
        // поиск минимального и максимального значений в массиве, а так же их позиций
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

    // вывод значений
    cout << "Минимальный элемент " << min_value << " находится в массиве под индексом " << pos_min << '\n';
    cout << "Максимальный элемент " << max_value << " находится в массиве под индексом " << pos_max << '\n';
    cout << "Сумма последних " << N << " элементов: " << last_n_elements_sum << endl;

    return 0;
}

int count_file_elements(ifstream &in)
{
    string str;
    int counter = 0;
    while(in >> str) counter++;

    reset_stream(in);
    return counter;
}

void reset_stream(ifstream &stream)
{
    stream.clear();
    stream.seekg(0L, std::ios_base::beg);
}

bool data_is_valid(ifstream  &in)
{
    string input;
    while (in >> input)
    {
        if (!is_numeric(input))
            return false;
    }
    reset_stream(in);
    return true;
}

bool is_numeric(const string& str)
{
    try{
        stod(str);
        return true;
    }
    catch (const exception &)
    {
        return false;
    }
}


