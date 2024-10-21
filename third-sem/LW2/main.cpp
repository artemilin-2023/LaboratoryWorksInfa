/******************************************************************
*                     КАФЕДРА № 304 2 КУРС                        *
*-----------------------------------------------------------------*
* Project Type  : Win32 Console Application                       *
* Project Name  : Sequences                                       *
* File Name     : main.cpp                                        *
* Language      : C/C++                                           *
* Programmer(s) : Романов Д.И., Ильин А.А                         *
* Modified By   :                                                 *
* Created       : 20/09/2024                                      *
* Last Revision : 05/10/2024                                      *
* Comment(s)    : Формирование массивов экспериментальных данных  *
******************************************************************/

#include <algorithm>
#include <iostream>
#include <random>
#include <fstream>
#include <filesystem>

#include "types.h"
#include "helpers.h"
#include "searches.h"

const int array_sizes[] = {
        10000,
        29000,
        48000,
        67000,
        86000,
        105000,
        124000,
        143000,
        162000,
        181000,
        200000,
};

void perform_searches_and_save(int* array, int array_size, const std::vector<search_with_name>& search_pack, const std::string& pack_name) {
    const std::vector<std::pair<int, std::string>> needles = {{10, "start"}, {array_size - 10, "end"}, {array_size / 2, "middle"}};

    auto outp_path = (std::filesystem::path("out")/pack_name/std::to_string(array_size)).replace_extension(".txt");
    std::filesystem::create_directories(outp_path.parent_path());
    std::ofstream fout(outp_path);
    fout << array_size;
    for (const auto& [_, needle_name]: needles) {
        fout << '|' << needle_name << " timing (ns)" << '|' << needle_name << " comparisons";
    }
    fout << '|' << "random" << " timing (ns)" << '|' << "random" << " comparisons" << '\n';

    for (const auto &current_search : search_pack) {
        fout << current_search.name;
        for (const auto& [needle_i, _]: needles) {
            int needle = array[needle_i];
            int* fixed_array = remove_number_from_array(array, array_size, needle);
            fixed_array[needle_i] = needle;
            search_result sort_result = current_search.func(fixed_array, array_size, needle);
            fout << '|' << std::chrono::duration_cast<std::chrono::nanoseconds>(sort_result.time_taken).count() << '|' << sort_result.comparison_count;
            delete[] fixed_array;
        }
        int needle = 42; // not in the loop because we don't need to put the number back in
        int* fixed_array = remove_number_from_array(array, array_size, needle);
        search_result sort_result = current_search.func(array, array_size, needle);
        fout << '|' << std::chrono::duration_cast<std::chrono::nanoseconds>(sort_result.time_taken).count() << '|' << sort_result.comparison_count << '\n';
        delete[] fixed_array;
    }
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

#define MAKE_FUNCTION_NAME_PAIR(func) {func, #func}
    const std::vector<search_with_name> unsorted_searches = {
            MAKE_FUNCTION_NAME_PAIR(better_linear_search),
            MAKE_FUNCTION_NAME_PAIR(sentinel_linear_search),
    };
    const std::vector<search_with_name> sorted_searches = {
            MAKE_FUNCTION_NAME_PAIR(ordered_array_search),
            MAKE_FUNCTION_NAME_PAIR(binary_search),
    };
#undef MAKE_FUNCTION_NAME_PAIR

    std::cout << "Current path is " << std::filesystem::current_path()
         << std::endl;

    // first, we're generating an unsorted array
    // then, we're testing it with each unsorted search:
    // - with the needle at the start (10th el)
    // - with the needle at the end (-10th el)
    // - with the needle in the middle
    // - with a random needle that's not in the array
    // * every time before searching we're ensuring ONLY ONE NEEDLE is in the haystack (where it should be)
    // ** fun fact: we're using a "search" function to do that lol
    // * there are two actual search functions: one is for measuring timing, the other one is for measuring comparisons
    // * BUT they're hidden behind a generic one, then the results are combined. ordered functions just have 0 as comparisons
    // then, we're sorting this array in asc order
    // then, we're testing it with each sorted search:
    // * the same steps as above, but we don't really need to ensure only one needle exists (since they're basically at the same spot)
    // * with the nonexistent needle, we can just copy the previous value over it if the needle exists beforehand

    // I'm picking 42 as the "random" needle each time since it's pretty close to the middle (uniform distribution)

    for (auto array_size: array_sizes) {
        int *array = generate_array(array_size, -array_size, array_size, gen);
        perform_searches_and_save(array, array_size, unsorted_searches, "unsorted");

        std::sort(array, array + array_size);
        perform_searches_and_save(array, array_size, sorted_searches, "sorted");
        delete[] array;
    }


//    for (auto& intFunc : intFuncs) { // Создание массивов и запись в файл для целочисленных функций
//        IntPoint* arr = GenerateArray(START_X, COUNT_X, intFunc);
//        WriteArrayToFile(arr, COUNT_X - 1, GetFilename());
//    }
//
//    for (auto& doubleFunc : doubleFuncs) { // Создание массивов и запись в файл для десятичных  функций
//        DoublePoint* arr = GenerateArray(START_X, COUNT_X, STEP_X, doubleFunc);
//        WriteArrayToFile(arr, COUNT_X - 1, GetFilename());
//    }
//    ofstream fout(GetFilename());
//    for (auto& f : intFuncs) { // Измерение времени создания целочисленных последовательностей
//        //ofstream fout(GetFilename());
//        for (auto& size : array_sizes) {
//            fout << fixed << setprecision(3) << GetAverageExecutionTime(f, size) << ' ';
//        }
//        fout << endl;
//    }
//    fout.close();
//    ofstream fout2(GetFilename());
//    for (auto& f : doubleFuncs) { // Измерение времени создания вещественных последовательностей
//        //ofstream fout(GetFilename());
//        for (auto& size : array_sizes) {
//            fout2 << fixed << setprecision(3) << GetAverageExecutionTimefordouble(f, STEP_X, size) << ' ';
//        }
//        fout2 << endl;
//        //fout.close();
//    }
//    fout2.close();

    return 0;
}
