/****************************************************************
*                     КАФЕДРА № 304 1 КУРС                      *
*---------------------------------------------------------------*
* Project Type  : Win32 Console Application                     *
* Project Name  : LW1                                           *
* File Name     : LW1.cpp                                       *
* Language      : C/C++                                         *
* Programmer(s) : Романов Д.И., Ильин А.А                       *
* Created at    : 20/02/24                                      *
* Last Revision : 20/02/24                                      *
* Comment(s)    : Строковые данные                              *
****************************************************************/



#define _USE_MATH_DEFINES
#define вперёд_славяне setlocale(LC_ALL, "ru_RU.UTF-8")

#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <filesystem>
#include <list>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

const string TEST_CASE = "test.txt";

const string TESTS_FOLDER_NAME = "tests";
const  string PATH_TO_TEST = ((fs::current_path() /= TESTS_FOLDER_NAME) /= TEST_CASE).u8string();

const int MINIMUM_ELEMENTS_IN_FILE = 2;

int count_file_elements(ifstream  &in);
void reset_stream(ifstream &stream, streampos start_pos);
const string remove_extra_white_spaces(const string text);
int count_chars_in_file(ifstream &in);
const string replace_symbols_in_longest_words(const string text);
int find_length_of_longest_word(string text);
pmr::vector<string> split_string(string text, const char seporator);
string join(pmr::vector<string> string_array, char seporator);

int main()
{
    int N; // Колличество символов в строке.
    //string text; // Считанный текст.
    ifstream file (PATH_TO_TEST); // Поток чтения из файла.

    if (!file.is_open())
    {
        cerr << "Ошибка открытия файла. Убедитесь, что по указанному пути файл существует: "
             << PATH_TO_TEST << '\n';
        return 1;
    }
    if (file.peek() == EOF)
    {
        cerr << "Файл пуст." << '\n';
        file.close();
        return 2;
    }
    if(count_file_elements(file) < MINIMUM_ELEMENTS_IN_FILE)
    {
        cerr << "В файле недостаточно данных. Минимальное колличество - " << MINIMUM_ELEMENTS_IN_FILE << '\n';
        file.close();
        return 3;
    }

    file >> N; cout << "N: " << N << '\n';
    if (N < 1)
    {
        cerr << "N не может быть меньше 1" << '\n';
        file.close();
        return 4;
    }
    if (count_chars_in_file(file) != N)
    {
        cerr << "N и колличество символов текста в файле не совпадают. Колличество символов - " << count_chars_in_file(file) << '\n';
        file.close();
        return 5;
    }

    const string text((istreambuf_iterator(file)), istreambuf_iterator<char>());
    cout << "Исходная строка: " << text << '\n';

    const string text_whithout_extra_white_space = remove_extra_white_spaces(text);
    cout << "Строка без лишних пробелов: " << text_whithout_extra_white_space << '\n';

    const string text_with_replaced_symbols = replace_symbols_in_longest_words(text);
    cout << "Текст, в котором в самых длинных словах первые и последние буквы поменялись местами: "
         << text_with_replaced_symbols << endl;


    file.close();
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

int count_chars_in_file(ifstream &in)
{
    auto start_position = in.tellg();
    int counter = 0;
    string line;

    while(getline(in, line))
    {
        counter += line.length();
    }

    reset_stream(in, start_position);

    return counter;
}

const string remove_extra_white_spaces(const string text)
{
    string result_text;
    size_t text_length =  text.length();
    for (int i = 0; i < text_length - 1; i++)
    {
        if (text[i] == ' ' && text[i + 1] == ' ')
            continue;

        result_text += text[i];
    }
    result_text += text[text_length - 1];

    return result_text;
}

const string replace_symbols_in_longest_words(const string text)
{
    int max_length = find_length_of_longest_word(text);
    auto words = split_string(text, ' ');

    for (int i = 0; i < words.size(); i++)
    {
        if (words[i].length() == max_length)
        {
            char tmp = words[i][0];
            words[i][0] = words[i][max_length - 1];
            words[i][max_length - 1] = tmp;
        }
    }

    return join(words, ' ');
}

int find_length_of_longest_word(string text)
{
    int counter = 0;
    int max_length = INT_MIN;

    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == ' ')
        {
            max_length = max(counter, max_length);
            counter = 0;
            continue;
        }
        
        counter++;
    }

    return max_length;
}

pmr::vector<string> split_string(string text, const char seporator)
{
    pmr::vector<string> result;
    string current_word;

    for (int i = 0; i < text.length(); i++)
    {
        if(text[i] == seporator)
        {
            result.push_back(current_word);
            current_word = "";
            continue;
        }

        current_word += text[i];
    }

    if (!current_word.empty())
        result.push_back(current_word);

    return result;
}

string join(pmr::vector<string> string_array, char seporator)
{
    string result;
    for (int i = 0; i < string_array.size() - 1; i++)
    {
        result += string_array[i] + seporator;
    }
    result += string_array.back();

    return result;
}
