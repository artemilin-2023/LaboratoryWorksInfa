//
// Created by y7o4ka on 26.10.2024.
//

#include <iostream>
#include "../searches.h"
#include "../helpers.h"

using hrc = std::chrono::high_resolution_clock;


int timed_ordered_array_search(int const *const array, int size, int needle, search_result &res) {
    // idc the reason behind this being its own "algorithm" but honestly idc
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

search_result ordered_array_search(int const *const array, int size, int needle, int correct_index) {
    search_result res{};

    print_search_result("timed OAS", [&] { return timed_ordered_array_search(array, size, needle, res); }, correct_index);

    return res;
};