//
// Created by y7o4ka on 26.10.2024.
//

#include "../searches.h"

#include "../helpers.h"

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

    print_search_result("timed BLS", [&] { return timed_better_linear_search(array, size, needle, res); }, correct_index);
    print_search_result("counted BLS", [&] { return timed_better_linear_search(array, size, needle, res); }, correct_index);

    return res;
};