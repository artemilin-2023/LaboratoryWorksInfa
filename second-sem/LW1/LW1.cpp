/****************************************************************
 *                     КАФЕДРА № 304 1 КУРС                      *
 *---------------------------------------------------------------*
 * Project Type  : Win32 Console Application                     *
 * Project Name  : LW1                                           *
 * File Name     : LW1.cpp                                       *
 * Language      : C/C++                                         *
 * Programmer(s) : Романов Д.И., Ильин А.А                       *
 * Created at    : 20/02/24                                      *
 * Last Revision : 05/03/24                                      *
 * Comment(s)    : Строковые данные                              *
 ****************************************************************/

#define _USE_MATH_DEFINES

#include <iostream>
#include <filesystem>
#include <fstream>

const char TEST_CASE[] = "test.txt";
const char TESTS_FOLDER_NAME[] = "tests";

const std::string PATH_TO_TEST = ((std::filesystem::current_path() /= TESTS_FOLDER_NAME) /= TEST_CASE).string();

size_t str_len(const char *text);  // our own ffs
void swap_char(char &a, char &b);  // same
void reset_stream(std::ifstream &stream, const std::streampos start_pos);
bool validate_format(std::ifstream &in);
char *remove_extra_white_spaces(const char *input);
char *replace_symbols_in_longest_words(const char *input);

int main() {
    std::streamsize input_string_length;     // Ожидаемое количество символов в строке.
    char *input_string;                      // Считанный текст.
    std::ifstream input_file(PATH_TO_TEST);  // Поток чтения из файла.

    if (!input_file.is_open()) {
        std::cerr << "Ошибка открытия файла. Убедитесь, что по указанному пути существует файл: "
                  << PATH_TO_TEST << '\n';
        return -1;
    }

    if (input_file.peek() == EOF) {
        std::cerr << "Файл пуст.\n";
        return -2;
    }

    if (!validate_format(input_file)) {
        std::cerr << "В файле должны находиться длина строки и сама строка, разделенные только пробелом. Пример:\n";
        std::cerr << "13 Hello, world!\n";
        return -3;
    }

    input_file >> input_string_length;
    std::cout << "Ожидаемая длина строки: " << input_string_length << '\n';
    if (input_string_length < 1) {
        std::cerr << "Ожидаемая длина строки не может быть меньше 1!\n";
        input_file.close();
        return -4;
    }

    input_string = new char[input_string_length + 1];  // + NULL
    // we're getting only the first space
    // which is the delimeter between an int and a string
    input_file.get();
    // all of the following whitespace is part of the string
    input_file.getline(input_string, input_string_length + 1);  // + NULL

    std::cout << "Полученная исходная строка: [" << input_string << "]\n";

    if (input_file.fail()) {  // there are more symbols!!1
        std::cerr << "В файле больше символов, чем указано (должно быть " << input_string_length << ")!\n";
        return -5;
    }
    {
        size_t real_input_string_length = str_len(input_string);
        if (real_input_string_length != input_string_length) {
            std::cerr << "В файле содержится меньше символов (" << real_input_string_length << "), чем должно быть (" << input_string_length << ")!\n";
            return -6;
        }
    }
    if (input_file.peek() != EOF) {
        std::cerr << "В файле есть данные на строках, кроме первой!\n";
        return -7;
    }

    const char *text_whithout_extra_white_space = remove_extra_white_spaces(input_string);
    std::cout << "Строка без лишних пробелов: [" << text_whithout_extra_white_space << "]\n";

    const char* text_with_replaced_symbols = replace_symbols_in_longest_words(input_string);
    std::cout << "Текст, в котором в самых длинных словах первые и последние буквы поменялись местами: ["
         << text_with_replaced_symbols << "]\n";
}

char *remove_extra_white_spaces(const char *input) {
    char *result = new char[str_len(input) + 1];
    char *current_result = result;

    bool last_space = false;
    while (*input) {
        if (isspace(*input)) {
            if (!last_space) {
                last_space = true;
                *current_result++ = *input;
            }
        } else {
            last_space = false;
            *current_result++ = *input;
        }
        input++;
    }
    *current_result = '\0';
    return result;
}

char *replace_symbols_in_longest_words(const char *input) {
    char *result = new char[str_len(input) + 1];
    char *current_result = result;
    size_t longest_word = 0;
    char *word_start = NULL;

    do {
        if (isspace(*(input)) || *input == '\0') {
            // a word ended
            if (word_start && input - word_start > longest_word)
                longest_word = input - word_start;
            word_start = NULL;
        } else if (!word_start) {
            // started new word
            word_start = (char *) input;
        }

        *current_result++ = *input++;
    } while (*(input-1));

    current_result = result;
    do {
        if (isspace(*(current_result)) || !*(current_result)) {
            // a word ended
            if (word_start && current_result - word_start == longest_word)
                swap_char(*word_start, *(current_result-1));
            word_start = NULL;
        } else if (!word_start) {
            // started new word
            word_start = current_result;
        }
        current_result++;
    } while (*(current_result-1));
    return result;
}

size_t str_len(const char *text) {
    size_t c = 0;
    while (text[c] != '\0')
        ++c;
    return c;
}

void swap_char(char &a, char &b)
{
    char c(a);
    a = b;
    b = c;
}

void reset_stream(std::ifstream &stream, const std::streampos start_pos) {
    stream.clear();
    stream.seekg(start_pos);
}

bool validate_format(std::ifstream &in) {
    std::streamsize n;
    in >> n;
    // we're checking if there are actually any characters later in the code
    // here we're just checking if the data is in the right format
    bool c = in.peek() == ' ';
    reset_stream(in, std::ios_base::beg);
    return c;
}
