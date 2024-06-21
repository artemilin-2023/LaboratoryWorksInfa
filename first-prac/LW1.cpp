/****************************************************************
 *                     КАФЕДРА № 304 1 КУРС                      *
 *---------------------------------------------------------------*
 * Project Type  : Win32 Console Application                     *
 * Project Name  : LW1                                           *
 * File Name     : LW1.cpp                                       *
 * Language      : C/C++                                         *
 * Programmer(s) : Романов Д.И., Ильин А.А                       *
 * Created at    : 01/06/24                                      *
 * Last Revision : 05/06/24                                      *
 * Comment(s)    : Строковые данные                              *
 ****************************************************************/

#define _USE_MATH_DEFINES

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

size_t MAX_FLIGHTS_LEN = 30;


struct Flight {
    std::string model;
    std::string boardNumber;
    std::string landingTime;
    std::string airport;
};

size_t parse_input_destructive(std::ifstream &stream, Flight *flights, size_t max_flights);
void reset_stream(std::ifstream &stream, const std::streampos start_pos);

int main(int argc, char **argv) {
    setlocale(LC_ALL, "866");
    if(argc == 1) {
        std::cout << "Usage: " << argv[0] << " test_file" << '\n';
        return 0;
    }

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

    std::cout << "Исходный файл:\n";
    std::cout << input_file.rdbuf();
    std::cout << '\n';
    reset_stream(input_file, std::ios_base::beg);

    Flight *flights;
    size_t parsed_flights_len = parse_input_destructive(input_file, flights, MAX_FLIGHTS_LEN);

}

// initializes flights, returns number of elements
size_t parse_input_destructive(std::ifstream &stream, Flight *flights, size_t max_flights) {
    flights = new Flight[max_flights];
    size_t i = 0, parsed = 0;
    std::string line;
    while(std::getline(stream, line)) {
        ++i;
        std::cout << "Строка" << std::setw(4) << i << ": [" << line << "]\n";
        std::string model, 
            boardNumber,
            landingTime,
            airport;
        std::istringstream iline(line);
        iline >> model;
        if(iline.fail()) { // empty input
            std::cerr << "Ошибка! Строка:" << std::setw(4) << i << ". Недостаточно данных: пустая строка.\n";
            continue;
        }
        std::cout << "Модель: [" << model << "] ";
        if(iline.eof()) { // no more data
            std::cerr << "Ошибка! Строка:" << std::setw(4) << i << ". Недостаточно данных: преждевременно достигнут конец строки.\n";
            continue;
        }
        
        iline >> boardNumber;
        std::cout << "Бортовой номер: [" << boardNumber << "] ";
        if(iline.eof()) { // no more data
            std::cerr << "\nОшибка! Строка:" << std::setw(4) << i << ". Недостаточно данных: преждевременно достигнут конец строки.\n";
            continue;
        }

        iline >> landingTime;
        std::cout << "Время посадки: [" << landingTime << "] ";
        if(iline.eof()) { // no more data
            std::cerr << "\nОшибка! Строка:" << std::setw(4) << i << ". Недостаточно данных: преждевременно достигнут конец строки.\n";
            continue;
        }
        
        iline >> airport;
        if(iline.fail()) { // empty input
            std::cerr << "\nОшибка! Строка:" << std::setw(4) << i << ". Недостаточно данных: пустая строка.\n";
            continue;
        }
        std::cout << "Аэропорт: [" << airport << "]\n";
        if(!iline.eof()) { // non-empty input, BUT still more data
            std::cerr << "Ошибка! Строка:" << std::setw(4) << i << ". Избыток данных: не достигнут конец строки.\n";
            continue;
        }
    }
    return parsed;
}

void reset_stream(std::ifstream &stream, const std::streampos start_pos) {
    stream.clear();
    stream.seekg(start_pos);
}
