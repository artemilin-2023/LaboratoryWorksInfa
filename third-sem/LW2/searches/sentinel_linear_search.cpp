//
// Created by y7o4ka on 26.10.2024.
//

#include <memory>
#include <iostream>
#include "../searches.h"
#include "../helpers.h"

using hrc = std::chrono::high_resolution_clock;


int timed_sentinel_linear_search(int const *const array, int size, int needle, search_result &res) {
    // the code above works because we don't modify the array (it's the same each time), so we do this just in case
    // it doesn't affect the computation in any way
    std::unique_ptr<int[]> temp_array(new int[size]); // freed when out of scope
    std::copy(array, array + size, temp_array.get());

    auto start = hrc::now();

    int last = temp_array[size - 1];
    temp_array[size - 1] = needle;

    int i = 0;
    while (temp_array[i] != needle)
        i++;

    temp_array[size - 1] = last;

    if ((i < size - 1) || (temp_array[size - 1] == needle)) {
        // found
        res.time_taken = hrc::now() - start;
        return i;
    }
    //not found
    res.time_taken = hrc::now() - start;
    return -1;
}

int counted_sentinel_linear_search(int const *const array, int size, int needle, search_result &res) {
    std::unique_ptr<int[]> temp_array(new int[size]);
    std::copy(array, array + size, temp_array.get());

    int last = temp_array[size - 1];
    temp_array[size - 1] = needle;

    int i = 0;
    while (temp_array[i] != needle) {
        ++res.comparison_count;
        ++i;
    }

    temp_array[size - 1] = last;

    ++res.comparison_count; // check if found
    if (i < size - 1)
        // found
        return i;
    ++res.comparison_count; // check the last element too
    if (temp_array[size - 1] == needle)
        // found
        return i;
    //not found
    return -1;
}

search_result sentinel_linear_search(int const *const array, int size, int needle, int correct_index) {
    search_result res{};

    print_search_result("timed SLS", [&] { return timed_sentinel_linear_search(array, size, needle, res); }, correct_index);
    print_search_result("counted SLS", [&] { return counted_sentinel_linear_search(array, size, needle, res); }, correct_index);

    return res;
};