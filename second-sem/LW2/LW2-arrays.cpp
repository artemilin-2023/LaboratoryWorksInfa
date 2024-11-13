
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

#include <iostream>
#include <fstream>
#include <limits>

// all matrices are in m[h][w] format

// reads the file and sets the matrix data. returns an error code
int read_file(const char* file_name, int** &matrix, int &height, int &width);
// processes the matrix using functions from the lw
void process_matrix(int** matrix, int height, int width);
// initializes matrix, then validates and reads a matrix from an ifstream. returns an error code
int validate_and_read_matrix(std::ifstream& in, int** &matrix, int &height, int &width);
// prints a matrix
void print_matrix(int const *const *matrix, int height, int width);
// returns a multiple of all negative elems above the main diagonal. returns 0 if no negative elements found
int mult_neg_elems_above_diag(int const *const *matrix, int height, int width);
// returns the minimum of all uneven elements. return 0 if no uneven elements found
int min_uneven_elems(int const *const *matrix, int height, int width);

int main(int argc, char **argv) {
    if(argc != 3) {
        std::cout << "Usage: " << argv[0] << " test_file_A test_file_B" << '\n';
        return 0;
    }

    int error;

    std::cout << "Файл 1: " << argv[1] << '\n';
    int **matrix1, height1, width1;
    error = read_file(argv[1], matrix1, height1, width1);
    if(!error)
        process_matrix(matrix1, height1, width1);

    std::cout << "Файл 2: " << argv[2] << '\n';
    int **matrix2, height2, width2;
    error = read_file(argv[2], matrix2, height2, width2);
    if(!error)
        process_matrix(matrix2, height2, width2);
}

int read_file(const char* file_name, int** &matrix, int &height, int &width) {
    std::ifstream input_file(file_name);

    if (!input_file.is_open()) {
        std::cerr << "Ошибка открытия файла. Убедитесь, что по указанному пути существует файл: "
                  << file_name << '\n';
        return -1;
    }

    if (input_file.peek() == EOF) {
        std::cerr << "Файл " << file_name << " пуст.\n";
        return -2;
    }

    int e = validate_and_read_matrix(input_file, matrix, height, width);
    if(0 != e) {
        std::cerr << "В файле должны через пробел или новую строку находиться количество матриц, а затем для каждой высота, ширина, а затем элементы матрицы слева-направо, затем сверху-вниз. Пример:\n";
        std::cerr << "1\n2 3\n1 2 3\n4 5 6\n";
        std::cerr << "Исходный файл:\n";

        input_file.clear();
        input_file.seekg(std::ios_base::beg);

        char c;
        while(input_file.get(c))
            std::cerr << c;
        std::cerr << '\n';
        return e;
    }
    return 0;
}

void process_matrix(int** matrix, int height, int width) {
    std::cout << "Исходная матрица:\n";
    print_matrix(matrix, height, width);

    int task1 = mult_neg_elems_above_diag(matrix, height, width);
    if(task1 == 0)
        std::cout << "Негативных элементов выше главной диагонали нет!\n";
    else
        std::cout << "Произведение негативных элементов выше главной диагонали: " << task1 << '\n';

    int task2 = min_uneven_elems(matrix, height, width);
    if(task2 == 0)
        std::cout << "Нечётных элементов нет!\n";
    else
        std::cout << "Минимум среди нечётных элементов: " << task2 << '\n';
}

int validate_and_read_matrix(std::ifstream& in, int** &matrix, int &height, int &width) {
    int n;
    in >> height >> width;
    if(in.fail()) { // not numbers? not enough data? bad either way
        std::cerr << "Не удалось получить размерность матрицы.\n";
        if(in.eof())
            std::cerr << "Недостаточно данных в файле.\n";
        return -5;
    }
    std::cout << "Полученная размерность матрицы: " << height << 'x' << width << '\n';
    if(height < 1 || width < 1) {
        std::cerr << "Высота и ширина должны быть больше 0!'\n";
        return -6;
    }

    matrix = new int*[height];

    for(int i = 0; i < height; i++) {
        matrix[i] = new int[width];
        for(int j = 0; j < width; j++) {
            in >> n;

            if(in.fail()) { // not numbers? not enough data? bad either way
                std::cerr << "Ошибка получения данных данных " << i << "-го элемента матрицы.\n";
                if(in.eof())
                    std::cerr << "Недостаточно данных в файле.\n";
                return -5;
            }

            matrix[i][j] = n;
        }
    }

    in >> n;
    if(!in.eof()) { // there is more data?
        std::cerr << "В файле содержится больше данных, чем нужно для представления заданных матриц.\n";
        return -7;
    }
    return 0;
}

void print_matrix(const int*const* const matrix, int height, int width) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

int mult_neg_elems_above_diag(int const *const *matrix, int height, int width) {
    bool neg_found = false;
    int mult = 1;
    for(int i = 0; i < height; i++) {
        for(int j = i + 1; j < width; j++) {
            if(matrix[i][j] < 0) {
                neg_found = true;
                mult *= matrix[i][j];
            }
        }
    }
    if(!neg_found)
        return 0;
    return mult;
}

int min_uneven_elems(int const *const *matrix, int height, int width) {
    bool uneven_found = false;
    int min = std::numeric_limits<int>::max();
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(matrix[i][j] % 2 != 0) {
                uneven_found = true;
                min = matrix[i][j] < min ? matrix[i][j] : min;
            }
        }
    }
    if(!uneven_found)
        return 0;
    return min;
}
