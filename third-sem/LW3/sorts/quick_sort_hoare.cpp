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


void timed_quick_sort_hoare(int *const array, int size, sort_result &res) {
    auto start = hrc::now();

    std::stack<std::pair<int, int>> sort_stack{};

    sort_stack.emplace(0, size - 1);

    while (!sort_stack.empty()) {
        auto [low_i, high_i] = sort_stack.top();
        sort_stack.pop();
        if (low_i >= high_i)
            continue;

        int pivot = array[low_i];
        int i = low_i - 1, j = high_i + 1;

        while (true) {
            do {
                i++;
            } while (array[i] < pivot);

            do {
                j--;
            } while (array[j] > pivot);

            if (i >= j)
                break;

            std::swap(array[i], array[j]);
        }

        sort_stack.emplace(low_i, j);
        sort_stack.emplace(j + 1, high_i);
    }

    res.time_taken = hrc::now() - start;
}

void counted_quick_sort_hoare(int *const array, int size, sort_result &res) {
    std::stack<std::pair<int, int>> sort_stack{};

    sort_stack.emplace(0, size - 1);

    while (!sort_stack.empty()) {
        auto [low_i, high_i] = sort_stack.top();
        sort_stack.pop();

        ++res.comparison_count;
        if (low_i >= high_i)
            continue;

        int pivot = array[low_i];
        int i = low_i - 1, j = high_i + 1;

        while (true) {
            do {
                i++;
                ++res.comparison_count;
            } while (array[i] < pivot);

            do {
                j--;
                ++res.comparison_count;
            } while (array[j] > pivot);

            ++res.comparison_count;
            if (i >= j)
                break;

            ++res.swap_count;
            std::swap(array[i], array[j]);
        }

        sort_stack.emplace(low_i, j);
        sort_stack.emplace(j + 1, high_i);
    }
}

sort_result quick_sort_hoare(int const *const array, int size, int const *const sorted_array) {
    auto temp_array = std::make_unique_for_overwrite<int[]>(size);

    sort_result res{};

    std::cout << "Starting timed QUICK SORT HOARE. Got: " << std::flush;
    std::copy(array, array + size, temp_array.get());
    timed_quick_sort_hoare(temp_array.get(), size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    std::cout << "Starting counted QUICK SORT HOARE. Got: " << std::flush;
    std::copy(array, array + size, temp_array.get());
    counted_quick_sort_hoare(temp_array.get(), size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    return res;
};