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
#include <filesystem>



using namespace std;
using std::filesystem::current_path;


// Тесты
// Не корректные
const string FILE_NAME = "test.txt";       // Файла не существует
//const string FILE_NAME = "test2.txt";     // Файл пуст
//const string FILE_NAME = "test3.txt";     // Неверное количество данных
//const string FILE_NAME = "test4.txt";     // Файл содержит буквенные/спец символы
//const string FILE_NAME = "test5.txt";     // Некорректное значение N
//const string FILE_NAME = "test6.txt";     // Исходные данные не содержат положительных значений
//const string FILE_NAME = "test7.txt";     // Исходные данные содержат положительные значения на границе с N (не входят)

// Корректные
//const string FILE_NAME = "test8.txt";     // Все числа положительные
//const string FILE_NAME = "test9.txt";     // Положительные и отрицательные
//const string FILE_NAME = "test10.txt";     // Положительные на границе с N (входят), остальные - 0


const int ARRAY_LENGTH = 10; // длина массива
const int NUMBER_OF_ELEMENTS = 12;
const string  PATH_TO_TESTS = "./tests/";

int count_file_elements(ifstream &in);
bool data_is_valid(ifstream  &in);
void reset_stream(ifstream &stream, streampos start_pos);
bool is_numeric(const string& str);
bool first_n_elements_contains_positive_value(ifstream &file, int N);

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

    cout << "Test source: " << PATH_TO_TESTS + FILE_NAME << endl;
    ifstream file(PATH_TO_TESTS + FILE_NAME); // создание потока для чтения
    if (!file.is_open()) // файл не найден
    {
        cerr << "Ошибка открытия файла.\n";
        file.close(); // закрыть поток чтения
        return -1;
    }
    else if (file.peek() == EOF) // файл не содержит данных
    {
        cerr << "Файл пуст\n";
        file.close();
        return -2;
    }
    else if (count_file_elements(file) != NUMBER_OF_ELEMENTS) // файл содержит недостаточное количество данных
    {
        cerr << "В файле должно быть ровно " << NUMBER_OF_ELEMENTS << " элементов!\n";
        file.close();
        return -3;
    }
    else if (!data_is_valid(file)) // файл содержит буквенные/спец символы
    {
        cerr << "Ошибка данных: невозможно привести к типу  double\n";
        file.close();
        return -4;
    }

    file >> P >> N;
    cout << "P: " << P << "\n" << "N: " << N << endl;
    if (N <= 0 || N > ARRAY_LENGTH)
    {
        cerr << "N должно быть больше 0 и меньше " << ARRAY_LENGTH << '\n';
        file.close();
        return -5;
    }
    if (!first_n_elements_contains_positive_value(file, N))
    {
        cerr << "Исходные данные не содержат положительных значений среди первых " << N << '\n';
        file.close();
        return -6;
    }

    cout << "Исходный массив: ";
    while (file >> new_item && j < ARRAY_LENGTH) // чтение данных из файла и занесение их в массив
    {
        if (new_item > 0 && j < N) // суммирование положительных элементов среди первых N
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

    reset_stream(in, std::ios_base::beg);
    return counter;
}

void reset_stream(ifstream &stream, streampos start_pos)
{
    stream.clear();
    stream.seekg(start_pos);
}

bool data_is_valid(ifstream  &in)
{
    string input;
    while (in >> input)
    {
        if (!is_numeric(input))
            return false;
    }
    reset_stream(in, std::ios_base::beg);
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

bool first_n_elements_contains_positive_value(ifstream &file, int N)
{
    double value;
    auto pos = file.tellg();
    for (int i = 0; i < N; i++)
    {
        file >> value;
        if (value > 0)
        {
            reset_stream(file, pos);
            return true;
        }
    }
    return false;
}