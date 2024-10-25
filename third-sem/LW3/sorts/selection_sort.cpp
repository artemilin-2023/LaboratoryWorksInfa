//
// Created by y7o4ka on 26.10.2024.
//

#include <chrono>
#include <iostream>
#include <memory>
#include <stack>

#include "../sorts.h"
#include "../helpers.h"

using hrc = std::chrono::high_resolution_clock;


void timed_selection_sort(int *const array, int size, sort_result &res) {
    auto start = hrc::now();

    for (int i = 0; i < size; ++i) {
        int min_i = i;
        for (int j = i + 1; j < size; ++j) {
            if (array[j] < array[min_i])
                min_i = j;
        }
        std::swap(array[i], array[min_i]);
    }

    res.time_taken = hrc::now() - start;
}

void counted_selection_sort(int *const array, int size, sort_result &res) {
    for (int i = 0; ++res.comparison_count, i < size; ++i) {
        int min_i = i;
        for (int j = i + 1; ++res.comparison_count, j < size; ++j) {
            ++res.comparison_count;
            if (array[j] < array[min_i])
                min_i = j;
        }
        ++res.swap_count;
        std::swap(array[i], array[min_i]);
    }
}

sort_result selection_sort(int const *const array, int size, int const *const sorted_array) {
    auto temp_array = std::make_unique_for_overwrite<int[]>(size);

    sort_result res{};

    std::cout << "Starting timed SELECTION SORT. Got: " << std::flush;
    std::copy(array, array + size, temp_array.get());
    timed_selection_sort(temp_array.get(), size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    std::cout << "Starting counted SELECTION SORT. Got: " << std::flush;
    std::copy(array, array + size, temp_array.get());
    counted_selection_sort(temp_array.get(), size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    return res;
};