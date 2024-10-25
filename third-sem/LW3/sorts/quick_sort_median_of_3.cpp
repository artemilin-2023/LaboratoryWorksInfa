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


// returns index of median-of-3 between indices of array
inline int median_of_3(int const *const array, int low_i, int high_i) {
    int mid_i = ((high_i - low_i) >> 2) + low_i;
    int low = array[low_i], mid = array[mid_i], high = array[high_i];
    if (low > mid) {
        if (mid > high)
            return mid_i;
        else if (low > high) // low > mid < high
            return high_i;
        else
            return low_i;
    } else { // mid > low
        if (low > high)
            return low_i;
        else if (mid > high) // mid > low < high
            return high_i;
        else
            return mid_i;
    }
}

void timed_quick_sort_median_of_3(int *const array, int size, sort_result &res) {
    auto start = hrc::now();

    std::stack<std::pair<int, int>> sort_stack{};

    sort_stack.emplace(0, size - 1);

    while (!sort_stack.empty()) {
        auto [low_i, high_i] = sort_stack.top();
        sort_stack.pop();
        if (low_i >= high_i)
            continue;

        int median_i = median_of_3(array, low_i, high_i);
        std::swap(array[median_i], array[high_i]);
        int pivot = array[high_i];

        int i = low_i;

        for (int j = low_i; j < high_i; ++j) {
            if (array[j] <= pivot) {
                std::swap(array[i], array[j]);
                ++i;
            }
        }
        std::swap(array[i], array[high_i]);

        sort_stack.emplace(low_i, i - 1);
        sort_stack.emplace(i + 1, high_i);
    }

    res.time_taken = hrc::now() - start;
}


inline int median_of_3_counted(int const *const array, int low_i, int high_i, sort_result &res) {
    int mid_i = ((high_i - low_i) >> 2) + low_i;
    int low = array[low_i], mid = array[mid_i], high = array[high_i];
    ++res.comparison_count;
    if (low > mid) {
        ++res.comparison_count;
        if (mid > high)
            return mid_i;
        else {
            ++res.comparison_count;
            if (low > high) // low > mid < high
                return high_i;
            else
                return low_i;
        }
    } else { // mid > low
        ++res.comparison_count;
        if (low > high)
            return low_i;
        else {
            ++res.comparison_count;
            if (mid > high) // mid > low < high
                return high_i;
            else
                return mid_i;
        }
    }
}


void counted_quick_sort_median_of_3(int *const array, int size, sort_result &res) {
    std::stack<std::pair<int, int>> sort_stack{};

    sort_stack.emplace(0, size - 1);

    while (!sort_stack.empty()) {
        auto [low_i, high_i] = sort_stack.top();
        sort_stack.pop();

        ++res.comparison_count;
        if (low_i >= high_i)
            continue;

        int median_i = median_of_3_counted(array, low_i, high_i, res);
        std::swap(array[median_i], array[high_i]);
        int pivot = array[high_i];

        int i = low_i;

        for (int j = low_i; ++res.comparison_count, j < high_i; ++j) {
            ++res.comparison_count;
            if (array[j] <= pivot) {
                ++res.swap_count;
                std::swap(array[i], array[j]);
                ++i;
            }
        }
        ++res.swap_count;
        std::swap(array[i], array[high_i]);

        sort_stack.emplace(low_i, i - 1);
        sort_stack.emplace(i + 1, high_i);
    }
}

sort_result quick_sort_median_of_3(int const *const array, int size, int const *const sorted_array) {
    auto temp_array = std::make_unique_for_overwrite<int[]>(size);

    sort_result res{};

    std::cout << "Starting timed QUICK SORT MEDIAN. Got: " << std::flush;
    std::copy(array, array + size, temp_array.get());
    timed_quick_sort_median_of_3(temp_array.get(), size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    std::cout << "Starting counted QUICK SORT MEDIAN. Got: " << std::flush;
    std::copy(array, array + size, temp_array.get());
    counted_quick_sort_median_of_3(temp_array.get(), size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    return res;
};