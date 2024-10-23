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

void perform_searches_and_save(int const *const array, int array_size, const std::vector<search_with_name> &search_pack,
                               const std::string &pack_name) {
    const std::vector<needle_def> needles = {
            {array[array_size / 8],              array_size / 8,              true,  "start"},
            {array[array_size / 2],  array_size / 2,  true,  "middle"},
            {array[array_size * 7 / 8], array_size * 7 / 8, true,  "end"},
            {42,                     -1,              false, "doesn't exist"},
    };

    auto output_path = (std::filesystem::path("results") / pack_name / std::to_string(array_size)).replace_extension(
            ".txt");
    std::filesystem::create_directories(output_path.parent_path());
    std::ofstream fout(output_path);
    fout << array_size;

    for (const auto &current_search: search_pack) {
        fout << '|' << current_search.name << " timing (ns)" << '|' << current_search.name << " comparisons";
    }
    fout << '\n';

    std::cout << "##Started " << pack_name << " sorts" << '\n';
    for (const auto &needle: needles) {
        fout << needle.name;
        std::unique_ptr<int[]> fixed_array(remove_number_from_array(array, array_size, needle.needle));
        if (needle.should_restore_needle)
            fixed_array[needle.needle_index] = needle.needle;
        for (const auto &current_search: search_pack) {
            std::cout << "#Started " << current_search.name << " with the \"" << needle.name << "\" needle" << '\n';
            search_result sort_result = current_search.func(fixed_array.get(), array_size, needle.needle);
            std::cout << "!Finished " << current_search.name
                      << ". It took " << std::chrono::duration_cast<std::chrono::milliseconds>(sort_result.time_taken).count() << "ms"
                      << " and " << sort_result.comparison_count << " comparisons" << '\n';
            fout << '|' << std::chrono::duration_cast<std::chrono::nanoseconds>(sort_result.time_taken).count() << '|'
                 << sort_result.comparison_count;
        }

        fout << '\n';
    }
    std::cout << "!!Finished " << pack_name << " sorts" << '\n';
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

    return 0;
}
