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
#include "sorts.h"

const long array_sizes[] = {
        500,
        1000,
        10000,
        50000,
};

void perform_searches_and_save(int const *const array, long array_size, const std::vector<sort_with_name> &sort_pack,
                               const std::string &pack_name) {
    auto output_path = (std::filesystem::path("results") / pack_name
                        / std::to_string(array_size)).replace_extension(".txt");
    std::filesystem::create_directories(output_path.parent_path());
    std::ofstream fout(output_path);

    for (const auto &current_search: sort_pack) {
        fout << '|' << current_search.name << " timing (ns)" << '|' << current_search.name << " comparisons" << '|'
             << current_search.name << " swaps";
    }
    fout << '\n';

    std::cout << "##Started " << pack_name << " sorts with size " << array_size << '\n';
    fout << "results";

    auto sorted_array = std::make_unique_for_overwrite<int[]>(array_size);
    std::copy(array, array + array_size, sorted_array.get());
    std::sort(sorted_array.get(), sorted_array.get() + array_size);

    for (const auto &current_sort: sort_pack) {
        std::cout << "#Started " << current_sort.name << '\n';
        sort_result sort_result = current_sort.func(array, array_size, sorted_array.get());
        std::cout << "!Finished " << current_sort.name
                  << ". It took "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(sort_result.time_taken).count() << "ms"
                  << ", " << sort_result.comparison_count << " comparisons"
                  << " and " << sort_result.swap_count << " swaps" << '\n';
        fout << '|' << std::chrono::duration_cast<std::chrono::nanoseconds>(sort_result.time_taken).count() << '|'
             << sort_result.comparison_count << '|' << sort_result.swap_count;
    }

    fout << '\n';
    std::cout << "!!Finished " << pack_name << " sorts" << '\n';
}

int main() {
    std::random_device rd;
    auto random_number = rd();
//    unsigned random_number = 150444277;
    std::mt19937 gen(random_number);

#define MAKE_FUNCTION_NAME_PAIR(func) {func, #func}
    const std::vector<sort_with_name> sorts = {
            MAKE_FUNCTION_NAME_PAIR(selection_sort),
            MAKE_FUNCTION_NAME_PAIR(quick_sort_last),
            MAKE_FUNCTION_NAME_PAIR(quick_sort_median),
            MAKE_FUNCTION_NAME_PAIR(quick_sort_hoare),
    };
#undef MAKE_FUNCTION_NAME_PAIR

    std::cout << "Current path is " << std::filesystem::current_path() << '\n'
              << "Random seed is: " << random_number << '\n';

    for (auto array_size: array_sizes) {
        int *array = generate_array(array_size, -array_size, array_size, gen);
        perform_searches_and_save(array, array_size, sorts, "unsorted");
        std::sort(array, array + array_size, std::less{});
        perform_searches_and_save(array, array_size, sorts, "sorted (asc)");
        std::sort(array, array + array_size, std::greater{});
        perform_searches_and_save(array, array_size, sorts, "sorted (desc)");
    }

    return 0;
}
