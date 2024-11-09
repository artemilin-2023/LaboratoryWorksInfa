//
// Created by y7o4ka on 26.10.2024.
//

#include <iostream>
#include "../searches.h"

using hrc = std::chrono::high_resolution_clock;


int timed_better_linear_search(int const *const array, int size, int needle, search_result &res) {
    auto start = hrc::now();

    for (int i = 0; i < size; ++i) {
        if (array[i] == needle) {
            // found
            res.time_taken = hrc::now() - start;
            return i;
        }
    }
    // not found
    res.time_taken = hrc::now() - start;
    return -1;
}

int counted_better_linear_search(int const *const array, int size, int needle, search_result &res) {
    for (int i = 0; i < size; ++i) {
        ++res.comparison_count; // i < size
        ++res.comparison_count; // a_i == needle
        if (array[i] == needle) {
            // found
            return i;
        }
    }
    // not found
    return -1;
}

search_result better_linear_search(int const *const array, int size, int needle, int correct_index) {
    search_result res{};

    std::cout << "Starting timed BLS. Correct index: " << correct_index << ". Got: ";
    int timed_index = timed_better_linear_search(array, size, needle, res);
    std::cout << timed_index << ". " << (timed_index == correct_index ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    std::cout << "Starting counted BLS. Correct index: " << correct_index << ". Got: ";
    int counted_index = counted_better_linear_search(array, size, needle, res);
    std::cout << counted_index << ". " << (counted_index == correct_index ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    return res;
};