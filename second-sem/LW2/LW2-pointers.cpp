
/****************************************************************
 *                     КАФЕДРА № 304 1 КУРС                      *
 *---------------------------------------------------------------*
 * Project Type  : Win32 Console Application                     *
 * Project Name  : LW2                                           *
 * File Name     : LW2.cpp                                       *
 * Language      : C/C++                                         *
 * Programmer(s) : Романов Д.И., Ильин А.А                       *
 * Created at    : 20/02/24                                      *
 * Last Revision : 05/03/24                                      *
 * Comment(s)    : Двумерные массивы                             *
 ****************************************************************/

#define _USE_MATH_DEFINES

#include <iostream>
#include <filesystem>
#include <fstream>
#include <limits>

size_t str_len(const char *text);  // our own ffs
void swap_char(char &a, char &b);  // same
void reset_stream(std::ifstream &stream, const std::streampos start_pos);
int validate_data(std::ifstream &in);
int mult_neg_elems_above_diag(int* arr, size_t height, size_t width);
int min_uneven_elems(int* arr, size_t length);

int main(int argc, char **argv) {
    if(argc == 1) {
        std::cout << "Usage: " << argv[0] << " test_file" << '\n';
        return 0;
    }

    size_t matrix_amount;
    std::ifstream input_file(argv[1]);  // Поток чтения из файла.

    if (!input_file.is_open()) {
        std::cerr << "Ошибка открытия файла. Убедитесь, что по указанному пути существует файл: "
                  << argv[1] << '\n';
        return -1;
    }

    if (input_file.peek() == EOF) {
        std::cerr << "Файл пуст.\n";
        return -2;
    }

    if (int ecode = validate_data(input_file); ecode != 0) {
        std::cerr << "В файле должны через пробел или новую строку находиться количество матриц, а затем для каждой высота, ширина, а затем элементы матрицы слева-направо, затем сверху-вниз. Пример:\n";
        std::cerr << "1\n2 3\n1 2 3\n4 5 6\n";
        std::cerr << "Исходный файл:\n";
        char c;
        while(input_file.get(c))
            std::cerr << c;
        std::cerr << '\n';
        return ecode;
    }

    input_file >> matrix_amount;
    for(size_t m_i = 0; m_i < matrix_amount; m_i++) {
        std::cout << m_i+1 << "-я матрица: \n";
        size_t height, width;
        input_file >> height >> width;
        int *arr = new int[height*width];
        for(int *arr_cur = arr, *arr_end = arr + height*width; arr_cur < arr_end; arr_cur++) {
            int n; input_file >> n;
            *arr_cur = n;
            std::cout << n << ' ';
            if((arr_cur - arr) % width == width-1)
                std::cout << '\n';
        }
        int task1 = mult_neg_elems_above_diag(arr, height, width);
        if(task1 == 0)
            std::cout << "Негативных элементов выше главной диагонали нет!\n";
        else
            std::cout << "Произведение негативных элементов выше главной диагонали: " << task1 << '\n';

        int task2 = min_uneven_elems(arr, height * width);
        if(task2 == 0)
            std::cout << "Нечётных элементов нет!\n";
        else
            std::cout << "Минимум среди нечётных элементов: " << task2 << '\n';
        std::cout << '\n';
    }
}

int mult_neg_elems_above_diag(int* arr_start, size_t height, size_t width) {
    bool neg_found = false;
    int mult = 1;
    int shift = 0;
    int *arr_cur = arr_start;
    int *arr_end = arr_start + height*width;
    while(arr_cur < arr_end) {
        if((arr_cur - arr_start) % width == 0) {
            arr_cur += ++shift;
        }
        if(*arr_cur < 0) {
            neg_found = true;
            mult *= *arr_cur;
        }
        arr_cur++;
    }
    if(!neg_found)
        return 0;
    return mult;
}

int min_uneven_elems(int* arr, size_t length) {
    bool uneven_found = false;
    int min = std::numeric_limits<int>::max();
    int* arr_end = arr + length;
    while(arr < arr_end) {
        if(*arr % 2 == 0) {
            uneven_found = true;
            min = *arr < min ? *arr : min;
        }
        arr++;
    }
    if(!uneven_found)
        return 0;
    return min;
}

void reset_stream(std::ifstream &stream, const std::streampos start_pos) {
    stream.clear();
    stream.seekg(start_pos);
}

int validate_data(std::ifstream &in) {
    int m_amt, N, M, n;
    in >> m_amt; // number of matrices to process
    if(in.fail()) { // not numbers? not enough data? bad either way
        std::cerr << "Не удалось получить количество матриц из файла.\n";
        if(in.eof())
            std::cerr << "Недостаточно данных в файле.\n";
        reset_stream(in, std::ios_base::beg);
        return -4;
    }

    std::cout << "Полученное количество матриц: " << m_amt << '\n';
    if(m_amt < 1) {
        std::cerr << "Количество матриц должно быть больше нуля!\n";
        return -5;
    }
    for(size_t m_i = 0; m_i < m_amt; m_i++) {
        in >> N >> M;
        if(in.fail()) { // not numbers? not enough data? bad either way
            std::cerr << "Не удалось получить размерность " << m_i << "-й матрицы.\n";
            if(in.eof())
                std::cerr << "Недостаточно данных в файле.\n";
            reset_stream(in, std::ios_base::beg);
            return -4;
        }
        std::cout << "Полученная размерность " << m_i+1 << "-й матрицы: " << N << 'x' << M << '\n';
        if(N < 1 || M < 1) {
            std::cerr << "Высота и ширина должны быть больше 0!'\n";
            return -5;
        }

        for(size_t i = 0; i < N*M; i++) {
            in >> n; // just try to get all data for this matrix

            if(in.fail()) { // not numbers? not enough data? bad either way
                std::cerr << "Ошибка получения данных данных " << i << "-го элемента " << m_i << "-й матрицы.\n";
                if(in.eof())
                    std::cerr << "Недостаточно данных в файле.\n";
                reset_stream(in, std::ios_base::beg);
                return -4;
            }
        }
    }
    in >> n;
    if(!in.eof()) { // there is more data..?
        std::cerr << "В файле содержится больше данных, чем нужно для представления заданных матриц.\n";
        reset_stream(in, std::ios_base::beg);
        return -6;
    }
    reset_stream(in, std::ios_base::beg);
    return 0;
}
